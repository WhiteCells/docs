#include <math.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include "driver/i2s_std.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/*
  I2S 麦克风 RMS 例程

  默认接线，以 INMP441 为例：
  - VCC  -> 3V3
  - GND  -> GND
  - SCK  -> GPIO 5
  - WS   -> GPIO 6
  - SD   -> GPIO 7
  - L/R  -> GND

  如果你的板子这些引脚被占用，请改下面的宏。
*/

#define I2S_MIC_BCLK GPIO_NUM_5
#define I2S_MIC_WS GPIO_NUM_6
#define I2S_MIC_DIN GPIO_NUM_7
#define SAMPLE_RATE 16000
#define FRAME_SAMPLES 320 // 20 ms at 16 kHz

static const char *TAG = "i2s_mic_rms";
static i2s_chan_handle_t rx_chan;

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
            .invert_flags = {
                .mclk_inv = false,
                .bclk_inv = false,
                .ws_inv = false,
            },
        },
    };
    ESP_ERROR_CHECK(i2s_channel_init_std_mode(rx_chan, &std_cfg));
    ESP_ERROR_CHECK(i2s_channel_enable(rx_chan));
}

void app_main(void)
{
    i2s_mic_init();

    int32_t samples[FRAME_SAMPLES];

    while (true) {
        size_t bytes_read = 0;
        ESP_ERROR_CHECK(i2s_channel_read(rx_chan, samples, sizeof(samples), &bytes_read, portMAX_DELAY));

        int sample_count = bytes_read / sizeof(int32_t);
        int32_t min_sample = INT32_MAX;
        int32_t max_sample = INT32_MIN;
        double sum_square = 0;

        for (int i = 0; i < sample_count; i++) {
            int32_t s = samples[i] >> 14; // 很多 I2S 麦克风有效位在高位，先缩到便于观察的范围
            if (s < min_sample) {
                min_sample = s;
            }
            if (s > max_sample) {
                max_sample = s;
            }
            sum_square += (double)s * (double)s;
        }

        double rms = sqrt(sum_square / sample_count);
        ESP_LOGI(TAG, "samples=%d min=%" PRId32 " max=%" PRId32 " rms=%.2f", sample_count, min_sample, max_sample, rms);
    }
}
