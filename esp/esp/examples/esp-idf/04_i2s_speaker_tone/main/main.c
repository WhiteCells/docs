#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include "driver/i2s_std.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/*
  I2S 扬声器正弦波提示音例程

  默认接线，以 MAX98357A 为例：
  - VIN  -> 5V 或 3V3，按模块说明选择
  - GND  -> GND
  - BCLK -> GPIO 15
  - LRC  -> GPIO 16
  - DIN  -> GPIO 17
  - SPK+ / SPK- -> 扬声器
*/

#define I2S_SPK_BCLK GPIO_NUM_15
#define I2S_SPK_WS GPIO_NUM_16
#define I2S_SPK_DOUT GPIO_NUM_17
#define SAMPLE_RATE 16000
#define TONE_HZ 440
#define FRAME_SAMPLES 320

static const char *TAG = "i2s_speaker";
static i2s_chan_handle_t tx_chan;

static void i2s_speaker_init(void)
{
    i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_AUTO, I2S_ROLE_MASTER);
    ESP_ERROR_CHECK(i2s_new_channel(&chan_cfg, &tx_chan, NULL));

    i2s_std_config_t std_cfg = {
        .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(SAMPLE_RATE),
        .slot_cfg = I2S_STD_PHILIPS_SLOT_DEFAULT_CONFIG(I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_MONO),
        .gpio_cfg = {
            .mclk = I2S_GPIO_UNUSED,
            .bclk = I2S_SPK_BCLK,
            .ws = I2S_SPK_WS,
            .dout = I2S_SPK_DOUT,
            .din = I2S_GPIO_UNUSED,
            .invert_flags = {
                .mclk_inv = false,
                .bclk_inv = false,
                .ws_inv = false,
            },
        },
    };
    ESP_ERROR_CHECK(i2s_channel_init_std_mode(tx_chan, &std_cfg));
    ESP_ERROR_CHECK(i2s_channel_enable(tx_chan));
}

void app_main(void)
{
    i2s_speaker_init();

    int16_t frame[FRAME_SAMPLES];
    double phase = 0;
    double step = 2.0 * M_PI * TONE_HZ / SAMPLE_RATE;

    ESP_LOGI(TAG, "playing %d Hz tone", TONE_HZ);

    while (true) {
        for (int i = 0; i < FRAME_SAMPLES; i++) {
            frame[i] = (int16_t)(sin(phase) * 8000);
            phase += step;
            if (phase > 2.0 * M_PI) {
                phase -= 2.0 * M_PI;
            }
        }

        size_t bytes_written = 0;
        ESP_ERROR_CHECK(i2s_channel_write(tx_chan, frame, sizeof(frame), &bytes_written, portMAX_DELAY));
    }
}
