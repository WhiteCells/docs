# 01 USB、串口与烧录

这一章把 ESP32-S3 的 USB 连接和 ESP-IDF 烧录流程讲透。你只要能稳定完成 `build -> flash -> monitor`，后面的实验就顺了。

## 电脑应该看到什么

插上开发板后，电脑会出现一个新的串口设备。

Linux 常见：

```bash
ls /dev/ttyACM*
ls /dev/ttyUSB*
```

macOS 常见：

```bash
ls /dev/cu.usb*
```

Windows 常见：

```text
设备管理器 -> 端口 (COM 和 LPT) -> COMx
```

ESP32-S3 开发板可能通过两类方式提供串口：

| 方式 | 常见端口 | 说明 |
| --- | --- | --- |
| USB-UART 芯片 | `ttyUSB*`、`COMx` | CH340、CP210x、FTDI 等芯片负责串口 |
| ESP32-S3 原生 USB Serial/JTAG | `ttyACM*`、`COMx` | ESP32-S3 自带 USB Serial/JTAG 功能 |

两种都可以用于 ESP-IDF 烧录和日志。区别主要在驱动、板子接线和 USB 口标识。

## 安装驱动

如果电脑不识别串口：

- CH340 / CH343：安装 WCH 串口驱动。
- CP210x：安装 Silicon Labs CP210x 驱动。
- FTDI：现代系统通常自带，旧系统可能要装驱动。
- 原生 USB Serial/JTAG：新系统通常直接识别，Windows 旧环境可能需要更新驱动。

驱动装好后，重新插拔开发板。

## 串口权限

Linux 上如果能看到 `/dev/ttyUSB0` 或 `/dev/ttyACM0`，但烧录时报权限错误，把当前用户加入 `dialout` 组：

```bash
sudo usermod -aG dialout $USER
```

然后注销并重新登录。临时测试也可以：

```bash
sudo chmod a+rw /dev/ttyUSB0
```

端口名字要按你的实际情况替换。

## 烧录命令

进入一个示例工程：

```bash
cd examples/esp-idf/01_gpio_pwm_adc
idf.py set-target esp32s3
idf.py build
idf.py flash monitor
```

如果电脑上有多个串口，指定端口：

```bash
idf.py -p /dev/ttyUSB0 flash monitor
```

macOS 示例：

```bash
idf.py -p /dev/cu.usbserial-0001 flash monitor
```

Windows PowerShell 示例：

```powershell
idf.py -p COM5 flash monitor
```

退出监视器：

```text
Ctrl + ]
```

监视器常用快捷键：

| 快捷键 | 作用 |
| --- | --- |
| `Ctrl + ]` | 退出 monitor |
| `Ctrl + T` 再 `Ctrl + R` | 复位开发板 |
| `Ctrl + T` 再 `Ctrl + F` | 构建并烧录，取决于 ESP-IDF monitor 版本 |

## BOOT 手动下载流程

如果 `idf.py flash` 一直提示连接失败，手动进入下载模式：

1. 按住 `BOOT`。
2. 点按 `RESET`，然后松开 `RESET`。
3. 继续按住 `BOOT`，运行或等待 `idf.py flash` 开始连接。
4. 看到开始写入 Flash 后松开 `BOOT`。

有些板子没有 `RESET`，只有 `EN`，它就是复位键。

## 烧录失败怎么判断

### 只亮灯，没有串口

常见原因：

- USB 线只能充电。
- 插错 USB 口。
- 串口驱动没装。
- 开发板供电或焊接有问题。

先换一根确定能传数据的 USB 线。

### 能看到串口，但连接失败

常见日志类似：

```text
Connecting....
Failed to connect to ESP32-S3
```

处理：

- 按 BOOT 手动进入下载模式。
- 降低烧录波特率：

```bash
idf.py -b 460800 flash
```

或者更保守：

```bash
idf.py -b 115200 flash
```

- 换 USB 口，不要经过不稳定的 USB Hub。

### 烧录成功但 monitor 没日志

检查：

- 端口是否指定正确。
- 程序是否真的在运行，可按 `RESET`。
- 波特率通常是 115200；ESP-IDF monitor 默认会处理。
- 如果使用原生 USB 且固件改变了 USB 配置，复位后端口可能重新枚举。

### 串口不断打印重启

常见原因：

- 接线导致启动引脚电平异常。
- 程序崩溃或看门狗复位。
- 外设供电不足，尤其是 Wi-Fi 发射或扬声器播放时。
- GPIO 接到 5V，造成异常甚至损坏。

先拔掉所有外设，只保留 USB，烧录最简单示例验证板子。

## 两个 USB 口怎么选

有些 ESP32-S3 板子有两个 USB-C：

```text
[USB/UART]  通过 USB-UART 芯片
[USB/OTG]   连接 ESP32-S3 原生 USB D+/D-
```

建议：

- 初学烧录优先用 `USB/UART`、`COM`、`PROG` 那个口。
- 做 USB HID、USB MIDI、USB 摄像头、USB MSC 等设备功能时，才重点使用 `USB/OTG`。
- 如果只有 `USB/OTG`，通常也能用 ESP32-S3 的 USB Serial/JTAG 烧录和日志。

ESP32-S3 原生 USB 信号通常连接到芯片的 USB D- / D+ 引脚。很多资料会把它们标为 GPIO19/GPIO20，但开发板可能已经把它们固定接到 USB 口，普通实验里不要再把这两个脚拿去接 LED 或 I2S。

## 稳定连接小清单

- 用数据线，不用纯充电线。
- 先不接外设，确认空板能烧录。
- 端口明确时用 `idf.py -p 端口 flash monitor`。
- 烧录失败先按 BOOT，再降波特率。
- 串口权限解决后再反复测试。
- 供电不稳时换电脑 USB 口或外接稳定 5V。

## 下一步

继续读 [02 针脚、GPIO 与供电](02_pins_gpio_power.md)，避免因为接错脚导致烧录失败或外设没反应。
