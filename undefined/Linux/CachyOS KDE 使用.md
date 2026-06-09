# 常用包安装

```sh
paru -S \
fuse \
nekoray-bin \
throne \
google-chrome \
linuxqq \
wechat-bin \
wps-office wps-office-fonts ttf-wps-fonts ttf-ms-fonts freetype2-wps libtiff5 \
fcitx5 fcitx5-configtool fcitx5-chinese-addons fcitx5-gtk fcitx5-qt \
cmake \
gdb \
clang \
ninja \
visual-studio-code-bin \
telegram-desktop \
drawio-desktop \
flameshot \
qtcreator \
go \
rust \
nvm \
uv \
termius \
tabby \
obs-studio \
docker docker-compose \
mariadb \
redis \
datagrip \
nvtop \
kubectl \
virtualbox \
nginx \
cuda
```

```sh
echo 'export PATH=/opt/cuda/bin:$PATH' >> ~/.zshrc
echo 'export LD_LIBRARY_PATH=/opt/cuda/lib64:$LD_LIBRARY_PATH' >> ~/.zshrc
source ~/.zshrc
```

wayland

```sh
sudo vim ~/.config/environment.d/envvars.conf
```

```
GTK_IM_MODULE=fcitx
QT_IM_MODULE=fcitx
XMODIFIERS=@im=fcitx
```

x11

```sh
mkdir -p ~/.config/environment.d
cat > ~/.config/environment.d/99-fcitx5.conf << 'EOF'
QT_IM_MODULES=wayland;fcitx
QT_IM_MODULE=fcitx
EOF
```

更新镜像源

```sh
sudo cachyos-rate-mirrors
```
