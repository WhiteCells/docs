### ssh 连接 Linux

#### Linux

```sh
# 安装 ssh 服务
sudo pacman -S openssh

# 启动 ssh 服务
sudo systemctl start sshd

# 停止 ssh 服务
sudo systemctl stop sshd

# 自启 ssh 服务
sudo systemctl enable sshd

# 取消自启 ssh 服务
sudo systemctl disable sshd

# 查看 ssh 服务状态
sudo systemctl status sshd

# 安装 net-tools
sudo pacman -S net-tools
```

### Windows

下载 [Xshell](https://www.xshell.com/zh/free-for-home-school/) 和 [Xftp](https://www.xshell.com/zh/free-for-home-school/)

主机为 Linux ip 地址，端口号 22，互连网协议版本 IPv4

vscode 中插件下载 `Remote Development` 连接 Linux，在插件 SSH config 设置 HostName(ip) 和 User(Linux用户名)

```ini
Host <name>
    HostName <ip>
    User <user name>
```

### 公私钥认证

Xshell 和 Xftp 有记住密码功能，而在 vscode 中每一次连接 Linux 都要输入密码，需要对操作主机进行公私钥认证（公钥存储在服务器上，私钥存储在本地）来避免每次连接时输入密码。

Windows 中生成 ssh 密钥：

```cmd
cd C:/Users/Xuan/.ssh
ssh-keygen -t rsa -f "id_rsa_linux_ssh"

# 复制公钥到剪切板
type C:\Users\<Name>\.ssh\id_rsa_linux_ssh.pub | clip
```

Linux 添加 Windows 公钥：

```shell
# 路径 ~/.ssh/ 下创建一个文件 authorized_keys
touch ~/.ssh/authorized_keys
# authorized_keys 为配置文件 /etc/ssh/sshd_config 中的名称
# 将 Windows 公钥内容复制到该文件
vim ~/.ssh/authorized_keys
```

修改 Windows 中 vscode 插件的 Host 配置 `~/.ssh/config` ，指定私钥文件：

```ini
Host <name>
    HostName <ip>
    User <user>
    Port 22
    IdentityFile ~/.ssh/id_rsa_linux_ssh
```

### 使用 sshpass 自动连接服务器

安装 `sshpass`：

```sh
yay -S sshpass
```

使用脚本：

```sh
#!/bin/bash

# 定义 SSH 连接的相关信息
SSH_USER="user"
SSH_HOST="host"
SSH_PASSWORD="password"

# 使用 sshpass 命令进行 SSH 连接
sshpass -p "$SSH_PASSWORD" ssh "$SSH_USER"@"$SSH_HOST"
```

### SSH 上传文件到服务器

```sh
scp <path> <usr>@<ip>:<path>
# example
scp -r /home/pic root@45.23.12.33:/home/
```

