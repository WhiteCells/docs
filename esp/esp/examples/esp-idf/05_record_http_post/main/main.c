#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "driver/gpio.h"
#include "driver/i2s_std.h"
#include "esp_event.h"
#include "esp_heap_caps.h"
#include "esp_http_client.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/ringbuf.h"
#include "freertos/task.h"
#include "nvs_flash.h"

/*
  按键录音并 HTTP POST 上传 PCM

  接线：
  - INMP441 VCC -> 3V3, GND -> GND, SCK -> GPIO5, WS -> GPIO6, SD -> GPIO7, L/R -> GND
  - Button GPIO0 -> 按键 -> GND，内部上拉

  使用方法：
  1. 修改 WIFI_SSID、WIFI_PASS、UPLOAD_URL。
  2. 在电脑运行 tools/pcm_upload_server.py。
  3. 烧录本例程。
  4. 按一下按键，设备录 3 秒并上传 16 kHz/16 bit/mono PCM。
*/

#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASS "YOUR_WIFI_PASSWORD"
#define UPLOAD_URL "http://192.168.1.100:8000/upload"

#define BUTTON_GPIO GPIO_NUM_0
#define I2S_MIC_BCLK GPIO_NUM_5
#define I2S_MIC_WS GPIO_NUM_6
#define I2S_MIC_DIN GPIO_NUM_7

#define SAMPLE_RATE 16000
#define FRAME_SAMPLES 320
#define RECORD_SECONDS 3
#define RINGBUF_SIZE (64 * 1024)

#define WIFI_CONNECTED_BIT BIT0

static const char *TAG = "record_post";
static EventGroupHandle_t wifi_event_group;
static RingbufHandle_t audio_rb;
static i2s_chan_handle_t rx_chan;
static volatile bool recording = false;

static void wifi_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        ESP_LOGW(TAG, "Wi-Fi disconnected, reconnecting");
        xEventGroupClearBits(wifi_event_group, WIFI_CONNECTED_BIT);
        esp_wifi_connect();
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
        ESP_LOGI(TAG, "got ip: " IPSTR, IP2STR(&event->ip_info.ip));
        xEventGroupSetBits(wifi_event_group, WIFI_CONNECTED_BIT);
    }
}

static void wifi_init_sta(void)
{
    wifi_event_group = xEventGroupCreate();

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, wifi_event_handler, NULL, NULL));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, wifi_event_handler, NULL, NULL));

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = WIFI_SSID,
            .password = WIFI_PASS,
            .threshold.authmode = WIFI_AUTH_WPA2_PSK,
        },
    };
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
}

static void i2s_mic_init(void)
{
    i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_AUTO, I2S_ROLE_MASTER);
    ESP_ERROR_CHECK(i2s_new_channel(&chan_cfg, NULL, &rx_chan));

    i2s_std_config_t std_cfg = {
        .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(SAMPLE_RATE),
        .slot_cfg = I2S_STD_PHILIPS_SLOT_DEFAULT_CONFIG(I2S_DATA_BIT_WIDTH_32BIT, I2S_SLOT_MODE_MONO),
        .gpio_cfg = {
            .mclk = I2S_GPIO_UNUSED,
            .bclk = I2S_MIC_BCLK,
            .ws = I2S_MIC_WS,
            .dout = I2S_GPIO_UNUSED,
            .din = I2S_MIC_DIN,
        },
    };
    ESP_ERROR_CHECK(i2s_channel_init_std_mode(rx_chan, &std_cfg));
    ESP_ERROR_CHECK(i2s_channel_enable(rx_chan));
}

static esp_err_t http_event_handler(esp_http_client_event_t *evt)
{
    if (evt->event_id == HTTP_EVENT_ON_DATA && evt->data_len > 0) {
        ESP_LOGI(TAG, "server response: %.*s", evt->data_len, (char *)evt->data);
    }
    return ESP_OK;
}

static void audio_capture_task(void *arg)
{
    int32_t raw[FRAME_SAMPLES];
    int16_t pcm16[FRAME_SAMPLES];

    while (true) {
        size_t bytes_read = 0;
        ESP_ERROR_CHECK(i2s_channel_read(rx_chan, raw, sizeof(raw), &bytes_read, portMAX_DELAY));

        if (!recording) {
            continue;
        }

        int count = bytes_read / sizeof(int32_t);
        for (int i = 0; i < count; i++) {
            pcm16[i] = (int16_t)(raw[i] >> 14);
        }

        BaseType_t ok = xRingbufferSend(audio_rb, pcm16, count * sizeof(int16_t), pdMS_TO_TICKS(20));
        if (ok != pdTRUE) {
            ESP_LOGW(TAG, "audio ring buffer full, dropping frame");
        }
    }
}

static esp_err_t upload_pcm_buffer(uint8_t *data, int len)
{
    esp_http_client_config_t config = {
        .url = UPLOAD_URL,
        .method = HTTP_METHOD_POST,
        .event_handler = http_event_handler,
        .timeout_ms = 15000,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_http_client_set_header(client, "Content-Type", "audio/L16; rate=16000; channels=1");
    esp_http_client_set_post_field(client, (const char *)data, len);

    esp_err_t err = esp_http_client_perform(client);
    if (err == ESP_OK) {
        ESP_LOGI(TAG, "upload ok, status=%d len=%d", esp_http_client_get_status_code(client), len);
    } else {
        ESP_LOGE(TAG, "upload failed: %s", esp_err_to_name(err));
    }
    esp_http_client_cleanup(client);
    return err;
}

static void clear_audio_ringbuffer(void)
{
    size_t item_size = 0;
    uint8_t *item = NULL;
    while ((item = (uint8_t *)xRingbufferReceive(audio_rb, &item_size, 0)) != NULL) {
        vRingbufferReturnItem(audio_rb, item);
    }
}

static void record_and_upload_once(void)
{
    const int target_bytes = SAMPLE_RATE * RECORD_SECONDS * sizeof(int16_t);
    uint8_t *record_buf = heap_caps_malloc(target_bytes, MALLOC_CAP_8BIT);
    if (!record_buf) {
        ESP_LOGE(TAG, "malloc record buffer failed");
        return;
    }

    clear_audio_ringbuffer();
    recording = true;
    ESP_LOGI(TAG, "recording %d seconds...", RECORD_SECONDS);

    int offset = 0;
    while (offset < target_bytes) {
        size_t item_size = 0;
        uint8_t *item = (uint8_t *)xRingbufferReceive(audio_rb, &item_size, pdMS_TO_TICKS(1000));
        if (!item) {
            ESP_LOGW(TAG, "wait audio timeout");
            continue;
        }

        int copy_len = item_size;
        if (offset + copy_len > target_bytes) {
            copy_len = target_bytes - offset;
        }
        memcpy(record_buf + offset, item, copy_len);
        offset += copy_len;
        vRingbufferReturnItem(audio_rb, item);
    }

    recording = false;
    ESP_LOGI(TAG, "record done, bytes=%d", offset);

    xEventGroupWaitBits(wifi_event_group, WIFI_CONNECTED_BIT, pdFALSE, pdTRUE, portMAX_DELAY);
    upload_pcm_buffer(record_buf, offset);
    free(record_buf);
}

static void button_task(void *arg)
{
    gpio_config_t button_cfg = {
        .pin_bit_mask = 1ULL << BUTTON_GPIO,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    ESP_ERROR_CHECK(gpio_config(&button_cfg));

    int last = 1;
    while (true) {
        int level = gpio_get_level(BUTTON_GPIO);
        if (last == 1 && level == 0) {
            vTaskDelay(pdMS_TO_TICKS(40));
            if (gpio_get_level(BUTTON_GPIO) == 0) {
                record_and_upload_once();
                while (gpio_get_level(BUTTON_GPIO) == 0) {
                    vTaskDelay(pdMS_TO_TICKS(10));
                }
            }
        }
        last = level;
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void app_main(void)
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ESP_ERROR_CHECK(nvs_flash_init());
    }

    audio_rb = xRingbufferCreate(RINGBUF_SIZE, RINGBUF_TYPE_BYTEBUF);
    if (!audio_rb) {
        ESP_LOGE(TAG, "create ring buffer failed");
        return;
    }

    wifi_init_sta();
    i2s_mic_init();

    xTaskCreate(audio_capture_task, "audio_capture", 4096, NULL, 6, NULL);
    xTaskCreate(button_task, "button", 8192, NULL, 4, NULL);
}
