# 09 排障速查表

这章按症状查。ESP32-S3 项目大多数问题都在 USB、供电、接线、GPIO 选择、Wi-Fi 网络和音频位宽这几类里。

## USB 和烧录

| 症状 | 常见原因 | 处理 |
| --- | --- | --- |
| 插 USB 只亮灯，没有串口 | USB 线只能充电、驱动缺失、插错口 | 换数据线，装 CH340/CP210x 驱动，换另一个 USB 口 |
| `Failed to connect` | 没进下载模式、自动下载电路不稳定 | 按住 BOOT，点 RESET，开始写入后松开 BOOT |
| 烧录中途失败 | 线或 Hub 不稳定、波特率太高 | 直连电脑，使用 `idf.py -b 115200 flash` |
| monitor 没日志 | 端口错、程序没启动、端口重新枚举 | 指定 `-p`，按 RESET，重新打开 monitor |
| Linux 权限错误 | 用户无串口权限 | `sudo usermod -aG dialout $USER` 后重新登录 |

## 启动和复位

| 症状 | 常见原因 | 处理 |
| --- | --- | --- |
| 一直进下载模式 | GPIO0 被外部电路拉低 | 松开 BOOT，检查外接按键，换普通 GPIO |
| 不断重启 | 供电不足、接线短路、程序崩溃 | 拔掉外设，只留 USB；看 reset reason |
| 接上外设才重启 | 3V3 被过载、5V 接到 GPIO、功放电流大 | 断电检查，功放单独供电并共地 |

## GPIO、LED、按键、ADC

| 症状 | 常见原因 | 处理 |
| --- | --- | --- |
| LED 不亮 | 极性反、电阻过大、GPIO 被占用 | 反转 LED，换 GPIO，确认 GND |
| LED 常亮不受控 | 接成低电平点亮但代码按高电平写 | 改接法或在代码中反相 |
| 按键乱跳 | 没上拉/下拉、接触抖动 | 启用内部上拉，增加消抖 |
| 按键按下读到 1 | 接法和代码逻辑相反 | 检查是否接到 3V3，调整逻辑 |
| ADC 一直 0 | 中间脚没接 ADC、GND 断 | 重新接电位器 |
| ADC 一直满值 | ADC 脚接到 3V3 或悬空 | 检查电位器和地线 |
| ADC 数值很飘 | 线太长、供电噪声、输入悬空 | 缩短线，确认电位器中间脚 |

## Wi-Fi 和 HTTP

| 症状 | 常见原因 | 处理 |
| --- | --- | --- |
| 一直断线重连 | 密码错、5 GHz 网络、信号弱 | 用 2.4 GHz，靠近路由器，先试手机热点 |
| got ip 后 HTTP 失败 | DNS、外网限制、URL 不通 | 换局域网 HTTP 服务测试 |
| 上传电脑失败 | IP 写错、防火墙、设备隔离 | 查电脑 IP，放行 8000 端口，关闭客户端隔离 |
| `127.0.0.1` 不通 | 这是 ESP32-S3 自己 | 用电脑的局域网 IP |
| 公司/校园网不通 | 网络隔离常见 | 用手机热点或家用路由器测试 |

## I2S 麦克风

| 症状 | 常见原因 | 处理 |
| --- | --- | --- |
| RMS 一直 0 | 没供电、BCLK/WS/SD 接错、L/R 不匹配 | 查接线，L/R 在 GND 和 3V3 间试 |
| RMS 一直很大 | 数据悬空、GND 不稳、位宽不匹配 | 重接 GND，缩短线，调整移位量 |
| 说话没变化 | 麦克风孔堵住、有效声道读错 | 改 L/R，检查 slot 配置 |
| 编译找不到 `i2s_std.h` | ESP-IDF 太旧 | 使用 ESP-IDF v5.1 或更新版本 |

## I2S 扬声器

| 症状 | 常见原因 | 处理 |
| --- | --- | --- |
| 没声音 | 功放没供电、BCLK/LRC/DIN 接反 | 按图重接，确认 SPK+/- 接扬声器 |
| 声音小 | 3V3 供电功率低、幅度小 | 按模块说明用 5V，适当增大幅度 |
| 声音破 | 幅度太大、供电不足 | 降低幅度，换稳定电源 |
| 一播放就重启 | USB 供电撑不住 | 功放单独 5V 供电并共地 |

## PCM 文件播放

| 症状 | 常见原因 | 处理 |
| --- | --- | --- |
| 播放速度不对 | 采样率参数错 | 使用 `-ar 16000` |
| 全是噪声 | 格式参数错或录音数据错 | 使用 `-f s16le -ac 1`，再回查麦克风 |
| 文件大小不对 | 录音时长或采样参数不一致 | 用公式 `采样率 * 字节数 * 声道 * 秒数` 检查 |

## 最小排障流程

遇到复杂问题，按这个顺序缩小范围：

1. 拔掉所有外设，只保留 USB，确认能烧录。
2. 跑实验 1，确认 GPIO、按键、ADC。
3. 跑实验 2，确认 Wi-Fi。
4. 单独跑实验 3，确认麦克风。
5. 单独跑实验 4，确认扬声器。
6. 最后跑实验 5，确认录音上传链路。

不要在“基础链路还没验证”的情况下直接调最终项目。一步一步来，问题会少很多。

## 官方参考

- ESP-IDF ESP32-S3 Get Started: https://docs.espressif.com/projects/esp-idf/en/stable/esp32s3/get-started/index.html
- ESP-IDF Build / Flash / Monitor: https://docs.espressif.com/projects/esp-idf/en/stable/esp32s3/get-started/start-project.html
- ESP-IDF GPIO driver and ESP32-S3 GPIO restrictions: https://docs.espressif.com/projects/esp-idf/en/stable/esp32s3/api-reference/peripherals/gpio.html
- ESP-IDF I2S driver: https://docs.espressif.com/projects/esp-idf/en/stable/esp32s3/api-reference/peripherals/i2s.html
- ESP-IDF ADC driver: https://docs.espressif.com/projects/esp-idf/en/stable/esp32s3/api-reference/peripherals/adc/index.html
