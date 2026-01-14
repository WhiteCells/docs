### Linux 环境配置 ESP  IDF

vscode 下载 ESP-IDF 插件，插件中找到 `Advanced`，`Configure ESP-IDF Extension` 选择 `ADVANCED`。

Select  download server 选择 Github 或镜像。

Select ESP-IDF version 选择 ESP-IDF 安装版本，如果已经存在则选择从系统中查找。

ESP-IDF Tools 也需要安装。

直接下一步就可以了。

部分 Linux 发行版可能没有必要的内核驱动。

```sh
uname -r # 查看当前运行的内核
sudo pacman -Syu linux612-headers linux612 # 安装对应的内核版本系列
sudo modprobe ftdi_sio
```

权限问题：

[Errno 13] could not open port /dev/ttyUSB0: [Errno 13] Permission denied: '/dev/ttyUSB0'

```sh
~ » ls -l /dev/ttyUSB0                                                                                                                    6 ↵ cells@pc
crw-rw---- 1 root uucp 188, 0  1月14日 17:36 /dev/ttyUSB0
```

```sh
sudo usermod -aG uucp $USER
```

记得注销。

.clangd 警告问题：

```.clangd
CompileFlags:
  Remove: [-std=c++*, -f*, -m*]
```

OpenOCD 问题：

无法调试

```sh
sudo cp \
$IDF_PATH/tools/tools/openocd-esp32/v0.12.0-esp32-20250707/openocd-esp32/share/openocd/contrib/60-openocd.rules \
/etc/udev/rules.d/

sudo udevadm control --reload-rules
sudo udevadm trigger
```

然后重新插拔 ESP32

查看权限变化：

```sh
ls -l /dev/bus/usb/*/*
```

修改 rule：

```.rules
# cat 99-espusb.rules                                                             cells@white
# ESP-Prog / ESP32 USB-JTAG
# SUBSYSTEM=="usb", ATTR{idVendor}=="303a", MODE="0666", GROUP="plugdev"
SUBSYSTEM=="usb", ATTR{idVendor}=="303a", MODE="0666"
```

