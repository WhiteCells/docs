# 02 针脚、GPIO 与供电

ESP32-S3 的 GPIO 很灵活，但不是所有脚都适合随便接外设。本章给出新手够用的选脚规则，让你能安全完成本教程的 LED、按键、ADC、I2S 麦克风和 I2S 功放。

## 先记住 5 条规则

1. GPIO 是 3.3V 逻辑，不耐 5V 输入。
2. 外设必须和 ESP32-S3 共地。
3. LED 必须串电阻，扬声器必须接功放。
4. GPIO0、GPIO45、GPIO46 等启动相关或特殊脚要谨慎。
5. 开发板已经占用的脚不要再拿来接外设。

## 开发板针脚不是芯片裸引脚

你看到的 `GPIO4`、`IO4` 是开发板把芯片 GPIO 引到排针后的名字。不同开发板可能把某些 GPIO 用在：

- 板载 RGB LED
- 板载按键
- LCD 或摄像头
- SPI Flash / PSRAM
- USB D+ / D-
- 电池检测
- 外置天线控制

所以换板子时，第一步是找该板子的 pinout 或原理图。

## 供电脚

| 丝印 | 典型含义 | 使用建议 |
| --- | --- | --- |
| `GND` | 地 | 所有模块都要接这里 |
| `3V3` / `3.3V` | 3.3V 输出 | 给 INMP441、电位器等小功耗模块供电 |
| `5V` / `VBUS` | USB 5V | 可给部分 MAX98357A 模块供电 |
| `VIN` | 外部输入或 5V 轨 | 看开发板说明，不要盲接 |
| `EN` | 芯片使能/复位 | 通常不接外设 |

不要从 GPIO 给模块供电。GPIO 只能输出信号，驱动能力有限。

## GPIO 输出：LED

LED 接法：

```text
GPIO2 -> 220 欧到 1k 欧电阻 -> LED 正极
LED 负极 -> GND
```

也可以反过来接成低电平点亮：

```text
3V3 -> 电阻 -> LED 正极
LED 负极 -> GPIO
```

本教程使用第一种，高电平点亮。

## GPIO 输入：按键

本教程按键接法：

```text
GPIO0 -> 按键 -> GND
```

程序中启用内部上拉：

```c
.pull_up_en = GPIO_PULLUP_ENABLE
```

因此：

```text
松开按键：GPIO 读到 1
按下按键：GPIO 读到 0
```

GPIO0 同时常用于 BOOT。做实验很方便，因为开发板上通常已经有 BOOT 键；做正式项目时，建议把按键换到 GPIO10、GPIO11、GPIO12、GPIO13、GPIO14 这类普通空闲脚。

## ADC 输入：电位器

本教程使用 GPIO4，对应 ESP32-S3 的 ADC1 通道之一。电位器接法：

```text
电位器一侧 -> 3V3
电位器另一侧 -> GND
电位器中间脚 -> GPIO4
```

注意：

- ADC 输入不要超过 3.3V。
- 读取到的是原始值，不是精确电压表。
- 如果要测电池或 5V 信号，必须先分压。
- Wi-Fi 开启时建议优先使用 ADC1 相关 GPIO，避免和无线功能资源冲突。

示例里配置了：

```c
#define ADC_CHANNEL ADC_CHANNEL_3 // GPIO4 on ESP32-S3
```

如果你换 ADC GPIO，也要查表修改 ADC 通道号。

## PWM：LEDC 外设

ESP32-S3 没有传统“模拟输出电压”，常用 LEDC PWM 让 LED 看起来变亮或变暗。

PWM 本质：

```text
占空比 0%    -> 一直低电平 -> 灭
占空比 50%   -> 一半时间高电平 -> 半亮
占空比 100%  -> 一直高电平 -> 全亮
```

示例使用 8 bit 分辨率，所以占空比范围是 0 到 255。

## I2S 麦克风选脚

INMP441 这类 I2S 麦克风有 3 根主要信号线：

| 麦克风 | ESP32-S3 | 方向 |
| --- | --- | --- |
| `SCK` / `BCLK` | GPIO5 | ESP32-S3 输出时钟 |
| `WS` / `LRCLK` | GPIO6 | ESP32-S3 输出帧同步 |
| `SD` / `DOUT` | GPIO7 | 麦克风输出音频到 ESP32-S3 |

ESP32-S3 的 I2S 可以通过 GPIO 矩阵映射到很多普通 GPIO。新手选脚原则：

- 避开 BOOT/启动脚。
- 避开 USB D+/D-。
- 避开板载 Flash/PSRAM、LCD、RGB LED 占用脚。
- 线尽量短，GND 接牢。

## I2S 功放选脚

MAX98357A 这类 I2S 功放接法：

| 功放 | ESP32-S3 | 方向 |
| --- | --- | --- |
| `BCLK` | GPIO15 | ESP32-S3 输出时钟 |
| `LRC` / `WS` | GPIO16 | ESP32-S3 输出帧同步 |
| `DIN` | GPIO17 | ESP32-S3 输出音频到功放 |

扬声器接到功放的 `SPK+` / `SPK-`，不要接到 ESP32-S3 GPIO。

功放供电：

- 小音量测试可用 3V3，具体看模块说明。
- 更常见是 `VIN -> 5V`，声音更大更稳。
- 5V 供电时仍必须和 ESP32-S3 共地。

## 本教程默认用脚表

| 用途 | GPIO | 是否可换 | 代码宏 |
| --- | --- | --- | --- |
| LED PWM | GPIO2 | 可换 | `LED_GPIO` |
| 按键 | GPIO0 | 可换，正式项目建议换 | `BUTTON_GPIO` |
| ADC 电位器 | GPIO4 | 可换，但要同步换 ADC channel | `ADC_CHANNEL` |
| 麦克风 BCLK | GPIO5 | 可换 | `I2S_MIC_BCLK` |
| 麦克风 WS | GPIO6 | 可换 | `I2S_MIC_WS` |
| 麦克风 DIN | GPIO7 | 可换 | `I2S_MIC_DIN` |
| 功放 BCLK | GPIO15 | 可换 | `I2S_SPK_BCLK` |
| 功放 WS | GPIO16 | 可换 | `I2S_SPK_WS` |
| 功放 DOUT | GPIO17 | 可换 | `I2S_SPK_DOUT` |

## 避免使用的脚

没有全局绝对答案，因为开发板差异很大。但新手优先避开：

- GPIO0：BOOT，实验可用，正式项目慎用。
- GPIO19/GPIO20：很多板子接原生 USB D- / D+。
- 连接 Flash/PSRAM 的脚：通常没有引到排针，但如果某些板子引出了，也不要用。
- 板载 RGB LED、LCD、摄像头、SD 卡已占用的脚。
- 只输入、只输出或启动电平敏感的特殊脚，除非你查过资料。

如果某个外设一直不工作，第一件事不是改代码，而是确认这个 GPIO 在你的开发板上真的可用。

## 接线检查表

- USB 断开时接线。
- `3V3` 没接到 `5V`。
- GND 共地。
- LED 串电阻。
- I2S 的 `BCLK`、`WS`、`DIN/DOUT` 没接反。
- 电位器中间脚接 ADC。
- 麦克风 VCC 接 3.3V。
- 功放输出只接扬声器，不接开发板 GPIO。

## 下一步

继续读 [03 ESP-IDF 环境](03_esp_idf_setup.md)，准备编译和烧录这些示例。
