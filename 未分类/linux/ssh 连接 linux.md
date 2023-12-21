### ssh 连接 Linux

```sh
# Linux
# 安装 ssh 服务
sudo apt install openssh-server

# 启动 ssh 服务
sudo systemctl start ssh
# sudo service ssh start

# 停止 ssh 服务
sudo systemctl stop ssh
# sudo service ssh stop

# 自启 ssh 服务
sudo systemctl enable ssh
# sudo service ssh enable

# 取消自启 ssh 服务
sudo systemctl disable ssh
# sudo service ssh disable

# 查看 ssh 服务
sudo systemctl status ssh
# sudo service ssh status

# 安装 net-tools
sudo apt install net-tools
```

下载 [Xshell](https://www.xshell.com/zh/free-for-home-school/) 和 [Xftp](https://www.xshell.com/zh/free-for-home-school/)

主机为 Linux inet 地址，端口号 22，互连网协议版本 IPv4

vscode 中插件下载 *Remote Development* 连接 Ubuntu，在插件 SSH config 设置 HostName(ip) 和 User(Ubuntu用户名)

### 公私钥认证

Xshell 和 Xftp 有记住密码功能，而在 vscode 中每一次连接 Linux 都要输入密码，需要对操作主机进行公私钥认证（公钥存储在服务器上，私钥存储在本地）来避免每次连接时输入密码

```cmd
# Windows 
# 生成公钥和私钥，已经存在则不需要生成
ssh-keygen -t rsa

# 复制公钥到剪切板
type C:\Users\[Name]\.ssh\id_rsa.pub | clip
```

```shell
# Linux
# 生成公钥和私钥，已经存在则不需要生成
ssh-keygen -t rsa
# 路径 ~/.ssh/ 下创建一个文件 authorized_keys
# 将公钥内容复制到该文件
vim ~/.ssh/authorized_keys
```

