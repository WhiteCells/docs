# ESP32-S3 ESP-IDF 联网语音项目教程

这是一套只使用 ESP-IDF 的 ESP32-S3 入门到语音链路实战教程。目标不是只跑一个 demo，而是把从 USB 连接、串口烧录、针脚选择、基础外设、Wi-Fi、I2S 麦克风、I2S 扬声器，到按键录音并 HTTP 上传的完整路径串起来。

项目默认目标板是通用 ESP32-S3 开发板，例如 ESP32-S3-DevKitC-1、ESP32-S3-N8R8、ESP32-S3-N16R8 一类板子。不同开发板的丝印和已占用 GPIO 可能不同，接线前请对照自己的开发板原理图。

## 你会完成什么

最终最小链路如下：

```text
USB-C 供电/烧录
    |
ESP32-S3
    |-- GPIO / LEDC / ADC：LED、按键、电位器
    |-- Wi-Fi：连接路由器并发 HTTP 请求
    |-- I2S RX：INMP441 麦克风采集 PCM
    |-- I2S TX：MAX98357A 功放播放提示音
    |-- HTTP POST：按键录音 3 秒并上传到电脑
```

进一步扩展后，它就是语音助手的骨架：

```text
按键或唤醒词 -> 录音 -> 上传 ASR -> 得到文本/意图 -> 执行控制 -> TTS/提示音播放
```

## 目录

```text
docs/
  00_hardware_overview.md         从开发板、USB 口、BOOT/RESET、面包板开始
  01_usb_serial_flash.md          USB 连接、串口识别、烧录、监视器、常见失败
  02_pins_gpio_power.md           ESP32-S3 针脚、供电、GPIO、ADC、I2S 选脚原则
  03_esp_idf_setup.md             ESP-IDF 安装、激活、创建/烧录工程
  04_experiment_gpio_pwm_adc.md   实验 1：GPIO + PWM + ADC
  05_experiment_wifi_http.md      实验 2：Wi-Fi + HTTP GET
  06_experiment_i2s_mic.md        实验 3：I2S 麦克风 RMS
  07_experiment_i2s_speaker.md    实验 4：I2S 功放提示音
  08_experiment_record_upload.md  实验 5：按键录音 + HTTP POST 上传
  09_troubleshooting.md           排障速查表
  assets/                         接线图 SVG
examples/
  esp-idf/
    01_gpio_pwm_adc/
    02_wifi_http/
    03_i2s_mic_rms/
    04_i2s_speaker_tone/
    05_record_http_post/
tools/
  pcm_upload_server.py            电脑端 PCM 上传测试服务器
```

本教程主线只使用 ESP-IDF。请从 `examples/esp-idf/` 开始。

## 推荐学习顺序

1. 读 [硬件总览](docs/00_hardware_overview.md)，确认开发板、USB 线、面包板和模块。
2. 读 [USB、串口与烧录](docs/01_usb_serial_flash.md)，先让电脑识别板子。
3. 读 [针脚和供电](docs/02_pins_gpio_power.md)，知道哪些脚适合接 LED、按键、ADC、I2S。
4. 读 [ESP-IDF 环境](docs/03_esp_idf_setup.md)，安装并激活 `idf.py`。
5. 按顺序完成 5 个实验，每个实验都有接线图、命令、现象和代码解析。

## 一条命令怎么烧录示例

进入任意 ESP-IDF 示例目录，例如：

```bash
cd examples/esp-idf/01_gpio_pwm_adc
idf.py set-target esp32s3
idf.py build
idf.py flash monitor
```

退出监视器：

```text
Ctrl + ]
```

如果你的板子有两个 USB 口，优先使用标着 `USB`、`UART`、`COM`、`PROG`、`Serial` 的口烧录。标着 `OTG`、`USB-OTG`、`Native USB` 的口通常也可以用，但需要板子和固件配置支持，细节见 [USB、串口与烧录](docs/01_usb_serial_flash.md)。

## 需要的硬件

最小基础实验：

- ESP32-S3 开发板 1 块
- USB 数据线 1 根
- 面包板和杜邦线
- LED 1 个
- 220 欧到 1k 欧电阻 1 个
- 按键 1 个
- 10k 电位器 1 个

语音实验：

- INMP441 或兼容 I2S 数字麦克风 1 个
- MAX98357A 或兼容 I2S 数字功放 1 个
- 4 欧或 8 欧小扬声器 1 个
- 稳定 USB 供电；扬声器声音较大时，建议功放用独立 5V，必须和 ESP32-S3 共地

## 默认接线

| 功能 | ESP32-S3 GPIO | 外设 |
| --- | --- | --- |
| LED PWM | GPIO2 | 串 220 欧电阻后接 LED |
| 按键 | GPIO0 | 按键另一端接 GND，程序使用内部上拉 |
| 电位器 ADC | GPIO4 / ADC1_CH3 | 中间脚接 GPIO4，两侧接 3V3/GND |
| I2S 麦克风 BCLK | GPIO5 | INMP441 SCK |
| I2S 麦克风 WS | GPIO6 | INMP441 WS |
| I2S 麦克风 DIN | GPIO7 | INMP441 SD |
| I2S 功放 BCLK | GPIO15 | MAX98357A BCLK |
| I2S 功放 WS | GPIO16 | MAX98357A LRC |
| I2S 功放 DOUT | GPIO17 | MAX98357A DIN |

这些 GPIO 是为了教学统一而选的。真实板子上如果 GPIO 被板载 LED、RGB、LCD、Flash/PSRAM 或其他外设占用，请按 [针脚和供电](docs/02_pins_gpio_power.md) 换脚，并同步修改代码里的宏。

## 5 个实验

| 实验 | 代码目录 | 你会学到 |
| --- | --- | --- |
| 1. GPIO + PWM + ADC | [examples/esp-idf/01_gpio_pwm_adc](examples/esp-idf/01_gpio_pwm_adc) | 按键输入、内部上拉、LEDC PWM、ADC 采样 |
| 2. Wi-Fi + HTTP | [examples/esp-idf/02_wifi_http](examples/esp-idf/02_wifi_http) | STA 模式、事件组、HTTP GET |
| 3. I2S 麦克风 | [examples/esp-idf/03_i2s_mic_rms](examples/esp-idf/03_i2s_mic_rms) | I2S RX、PCM、RMS 音量 |
| 4. I2S 扬声器 | [examples/esp-idf/04_i2s_speaker_tone](examples/esp-idf/04_i2s_speaker_tone) | I2S TX、正弦波 PCM、数字功放 |
| 5. 录音上传 | [examples/esp-idf/05_record_http_post](examples/esp-idf/05_record_http_post) | FreeRTOS 任务、环形缓冲、HTTP POST 上传音频 |

## 重要安全提醒

- ESP32-S3 GPIO 是 3.3V 逻辑，不要把 5V 信号直接接到 GPIO。
- 所有外设必须和 ESP32-S3 共地。
- LED 必须串限流电阻。
- 扬声器不能直接接 GPIO，需要功放模块。
- INMP441 这类 I2S 麦克风通常只接 3.3V。
- GPIO0 是启动模式相关引脚，也是很多开发板的 BOOT 键。教程为了方便使用它做按键，但产品项目建议换成普通 GPIO。
- 接线前断电，确认后再插 USB。

## 本仓库的验证状态

文档和示例代码按 ESP-IDF 工程结构组织。本环境当前没有安装 `idf.py`，所以这里无法实际编译；你在本机安装并激活 ESP-IDF 后，可以按每个实验文档中的命令构建和烧录。
