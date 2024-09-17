### 包管理器

[AUR(Arch User Repository)](https://aur.archlinux.org/packages)

### pacman 命令

```sh
# 安装指定的包及依赖项
sudo pacman -S package

# 包数据库中搜索指定的包名
sudo pacman -Ss package

# 更新包数据库
sudo pacman -Sy

# 强制更新包数据库
sudo pacman -Syy

# 将已安装的包升级到当前包数据库中的最新版本
sudo pacman -Su

# 更新包数据库，然后将已安装的包升级到当前包数据库中的最新版本
sudo pacman -Syu

# 强制更新包数据库，然后将已安装的包升级到当前包数据库中的最新版本
sudo pacman -Syyu
paru
paru -Syyu

# 删除当前未安装包的缓存
sudo pacman -Sc

# 删除已下载的包文件的缓存
sudo pacman -Scc

# 卸载指定的包
sudo pacman -R package

# 卸载指定的包及依赖
sudo pacman -Rs package

# 卸载指定的包及配置文件
sudo pacman -Rn package

# 卸载指定的包及依赖，但不删除配置文件
sudo pacman -Rc package

# 卸载指定的包、依赖及配置文件
sudo pacman -Rns package
paru -Rsc package

# 强制卸载指定的包及依赖
sudo pacman -Rdd package

# 查询已安装的包
sudo pacman -Q

# 查询已安裝的包，排除依赖
sudo pacman -Qe

# 在已安装的包中搜索包
sudo pacman -Qs package

# 查询孤立包
sudo pacman -Qdt

# 卸载孤立包
sudo pacman -Rns $(pacman -Qdtq)

# 安装本地的包
sudo pacman -U file.pkg.tar.zst
```

更新源

```sh
# 更新国内源
sudo pacman-mirrors -i -c China -m rank
```

安装 package

```sh
# AUR 助手
sudo pacman -S yay

# 安装 archlinux-keyring 以导入 GPG key
sudo pacman -S archlinux-keyring

yay -S base-devel

# fcitx5
yay -S fcitx5 fcitx5-configtool fcitx5-chinese-addons fcitx5-gtk fcitx5-qt
yay pacman -S fcitx5-input-support

yay -S google-chromium
# google chromium 无法使用系统代理，启动参数添加 --proxy-server=127.0.0.1:[port]

# clash-for-windows
yay -S clash-for-windows

# nekoray-bin
yay -S nekoray-bin

# java
yay -S jdk-openjdk

# visual-studio-code-bin
yay -S visual-studio-code-bin
# Window: Title Bar Style

# qtcreator
yay -S qtcreator

# qt6
yay -S qt6-base qt6-multimedia qt6-tools

# vim
yay -S vim

# gdb
yay -S gdb

# cmake
yay -S cmake

# make
yay -S make

# git
yay -S git

# obs-studio
yay -S obs-studio

# flameshot
yay -S flameshot # flameshot gui

# net-tools
yay -S net-tools

# linux qq
yay -S linuxqq

# qq music
yay -S qqmusic-electron

# Rong Rec
yay -S songrec
# songrec listen

# telegram
yay -S telegram-desktop

# drawio-desktop
yay -S drawio-desktop-bin

# timeshift
yay -S timeshift

# wps
yay -S wps-office-mui-zh-cn  wps-office-cn
yay -S wps-office-fonts ttf-wps-fonts ttf-ms-fonts
yay -S freetype2-wps # 解决字体变粗问题
yay -S libtiff5 # 解决导出 PDF 错误

# motrix
yay -S motrix-bin
```

fctix5 美化

```sh
git clone https://github.com/tonyfettes/fcitx5-nord.git
mkdir -p ~/.local/share/fcitx5/themes/
cd fcitx5-nord
cp -r Nord-Dark/ Nord-Light/ ~/.local/share/fcitx5/themes/

vim ~/.config/fcitx5/conf/classicui.conf
# 修改 Theme=Nord-Light
```

```sh
pacman -S fcitx5-material-color
```

kde 桌面环境无法打开 theme store

```sh
rm ~/.config/Trolltech.conf
kbuildsycoca5 --noincremental
```

