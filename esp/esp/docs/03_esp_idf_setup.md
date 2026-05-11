# 03 ESP-IDF 环境

本项目只使用 ESP-IDF。你需要安装 ESP-IDF，激活环境后获得 `idf.py` 命令。

## 推荐版本

建议使用 ESP-IDF v5.1 或更新版本，也可以使用当前官方 stable 版本。本项目示例使用新版 I2S 标准驱动头文件：

```c
#include "driver/i2s_std.h"
```

如果你使用 ESP-IDF v4.x，I2S API 差异较大，不建议直接照搬本仓库代码。

## 安装方式

最稳妥的安装方法是按 Espressif 官方文档安装：

- Windows：推荐 ESP-IDF Tools Installer 或 VS Code ESP-IDF 插件。
- macOS / Linux：推荐使用官方 `install.sh` 和 `export.sh`。

安装完成后，新开终端并激活 ESP-IDF 环境。Linux/macOS 典型命令：

```bash
. $HOME/esp/esp-idf/export.sh
```

如果你把 ESP-IDF 安装在其他目录，把路径替换成你的实际路径。

检查：

```bash
idf.py --version
```

能看到版本号，说明环境已激活。

## VS Code 用户

可以安装 Espressif 的 ESP-IDF 扩展。它会帮你配置：

- ESP-IDF 路径
- 工具链
- Python 虚拟环境
- 串口
- Build、Flash、Monitor 按钮

不过教程中的命令行方式仍然建议掌握，因为排障时更直接。

## 构建一个示例

以第一个实验为例：

```bash
cd examples/esp-idf/01_gpio_pwm_adc
idf.py set-target esp32s3
idf.py build
```

第一次构建会生成 `build/` 目录，时间会比较长。

## 烧录和查看日志

```bash
idf.py flash monitor
```

如果需要指定端口：

```bash
idf.py -p /dev/ttyUSB0 flash monitor
```

退出：

```text
Ctrl + ]
```

## 清理工程

普通重新配置：

```bash
idf.py reconfigure
```

删除构建产物：

```bash
idf.py fullclean
```

`fullclean` 会删掉当前示例的 `build/` 目录和配置缓存，不会删除源代码。

## 配置工程

打开 ESP-IDF 菜单配置：

```bash
idf.py menuconfig
```

本教程的示例尽量把配置写在 `main.c` 顶部宏里，减少初学者在菜单里找选项的成本。以后做正式项目，可以把 Wi-Fi 名称、密码、服务器地址等迁移到：

- `menuconfig`
- NVS
- 配网页面
- BLE 配网

## ESP-IDF 工程结构

每个示例都是独立工程：

```text
examples/esp-idf/01_gpio_pwm_adc/
  CMakeLists.txt
  main/
    CMakeLists.txt
    main.c
```

根 `CMakeLists.txt`：

```cmake
cmake_minimum_required(VERSION 3.16)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(esp32s3_01_gpio_pwm_adc)
```

`main/CMakeLists.txt`：

```cmake
idf_component_register(SRCS "main.c" INCLUDE_DIRS ".")
```

如果用到了数学库 `sin()` 或 `sqrt()`，对应示例会额外链接 `m`：

```cmake
target_link_libraries(${COMPONENT_LIB} PRIVATE m)
```

## 日志怎么看

ESP-IDF 常见日志格式：

```text
I (1234) gpio_pwm_adc: adc_raw=2048 pwm_duty=127 button=1
```

含义：

| 字段 | 说明 |
| --- | --- |
| `I` | INFO 级别，另有 `W`、`E` 等 |
| `(1234)` | 从启动到现在的毫秒数 |
| `gpio_pwm_adc` | 日志 TAG |
| 后面内容 | 程序打印的信息 |

示例里常用：

```c
ESP_LOGI(TAG, "message");
ESP_LOGW(TAG, "warning");
ESP_LOGE(TAG, "error");
```

## 修改 Wi-Fi 和服务器地址

涉及 Wi-Fi 的示例需要修改 `main.c` 顶部宏：

```c
#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASS "YOUR_WIFI_PASSWORD"
```

录音上传示例还要修改：

```c
#define UPLOAD_URL "http://192.168.1.100:8000/upload"
```

ESP32-S3 连接 2.4 GHz Wi-Fi，不支持只开 5 GHz 的路由器或热点。

## 学习时的推荐工作流

1. 只改一个地方。
2. `idf.py build` 看编译是否通过。
3. `idf.py flash monitor` 看现象和日志。
4. 记录你改了哪个 GPIO、哪个宏、串口输出是什么。
5. 出问题先恢复到上一个能工作的状态。

## 下一步

开始第一个实验：[04 GPIO + PWM + ADC](04_experiment_gpio_pwm_adc.md)。
