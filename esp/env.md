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

