### Debian

#### Debian

```sh
sudo cp /etc/apt/sources.list /etc/apt/sources.list.bak

sudo vim /etc/apt/sources.list

:%d

deb http://mirrors.tuna.tsinghua.edu.cn/debian bookworm main contrib non-free non-free-firmware
deb http://mirrors.tuna.tsinghua.edu.cn/debian bookworm-updates main contrib non-free non-free-firmware
deb http://mirrors.tuna.tsinghua.edu.cn/debian bookworm-backports main contrib non-free non-free-firmware
deb http://mirrors.tuna.tsinghua.edu.cn/debian-security bookworm-security main contrib non-free non-free-firmware
```

#### Ubuntu

```sh
# 备份源配置文件
cp /etc/apt/sources.list /etc/apt/old_sources.list

# 打开源配置文件
sudo vim /etc/apt/sources.list

# 清除原配置文件 (命令模式)
:%d

# 复制源镜像
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal-updates main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal-backports main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal-security main restricted universe multiverse

# Ubuntu 版本代号
# Ubuntu 23.04: lunar
# Ubuntu 22.04 LTS: jammy
# Ubuntu 22.10: kinetic
# Ubuntu 20.04 LTS: focal
# Ubuntu 18.04 LTS: bionic
# Ubuntu 16.04 LTS: xenial
# Ubuntu 16.04 LTS: trusty

# 更新软件包列表
sudo apt update
```

### RHEL

#### RedHel

#### CentOS

```sh
sudo vim /etc/yum.repos.d/CentOS-Base.repo



sudo yum clean all
sudo yum update
```



### Arch

#### Arch Linux

```sh
sudo vim /etc/pacman.d/mirrorlist

sudo pacman -Syu
```

### 开源镜像站

- https://mirror.tuna.tsinghua.edu.cn/help/ubuntu/
- https://mirrors.ustc.edu.cn/help/index.html