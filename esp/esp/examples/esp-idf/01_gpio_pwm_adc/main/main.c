#include <stdio.h>
#include <stdbool.h>
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LED_GPIO GPIO_NUM_2
#define BUTTON_GPIO GPIO_NUM_0
#define ADC_CHANNEL ADC_CHANNEL_3 // GPIO4 on ESP32-S3

static const char *TAG = "gpio_pwm_adc";

void app_main(void)
{
    gpio_config_t button_cfg = {
        .pin_bit_mask = 1ULL << BUTTON_GPIO,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    ESP_ERROR_CHECK(gpio_config(&button_cfg));

    ledc_timer_config_t timer_cfg = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_8_BIT,
        .timer_num = LEDC_TIMER_0,
        .freq_hz = 5000,
        .clk_cfg = LEDC_AUTO_CLK,
    };
    ESP_ERROR_CHECK(ledc_timer_config(&timer_cfg));

    ledc_channel_config_t channel_cfg = {
        .gpio_num = LED_GPIO,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0,
        .hpoint = 0,
    };
    ESP_ERROR_CHECK(ledc_channel_config(&channel_cfg));

    adc_oneshot_unit_handle_t adc_handle;
    adc_oneshot_unit_init_cfg_t adc_init_cfg = {
        .unit_id = ADC_UNIT_1,
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&adc_init_cfg, &adc_handle));

    adc_oneshot_chan_cfg_t adc_chan_cfg = {
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_handle, ADC_CHANNEL, &adc_chan_cfg));

    bool led_enabled = true;
    int last_button = 1;

    while (true) {
        int button = gpio_get_level(BUTTON_GPIO);
        if (last_button == 1 && button == 0) {
            led_enabled = !led_enabled;
            ESP_LOGI(TAG, "button pressed, led_enabled=%d", led_enabled);
            vTaskDelay(pdMS_TO_TICKS(40));
        }
        last_button = button;

        int raw = 0;
        ESP_ERROR_CHECK(adc_oneshot_read(adc_handle, ADC_CHANNEL, &raw));
        uint32_t duty = raw * 255 / 4095;

        ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, led_enabled ? duty : 0));
        ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0));

        ESP_LOGI(TAG, "adc_raw=%d pwm_duty=%lu button=%d", raw, (unsigned long)duty, button);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
