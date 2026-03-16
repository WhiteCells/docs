###

```sh
iptables -P INPUT ACCEPT
iptables -P OUTPUT ACCEPT
iptables -P FORWARD ACCEPT
iptables -F
```

```sh
apt install ufw
ufw default deny incoming
ufw default allow outgoing
ufw allow ssh
ufw allow 80
ufw allow 443
ufw allow 7890
ufw status
ufw enable
```

```sh
ufw default allow incoming
```

设置密码

```sh
passwd
passwd \<username\>
```

```
ssh 
```

```sh
sudo vim /etc/ssh/sshd_config
# 检查 /etc/ssh/sshd_config.d/* 是否有文件

#Port 22
#PasswordAuthentication yes

# 允许 root 使用密码登录
PermitRootLogin prohibit-password
PermitRootLogin yes
```

```sh
sudo systemctl restart ssh
```

如果 ssh 是由 ssh.socket 决定的

```sh
sudo systemctl stop ssh.socket
sudo systemctl disable ssh.socket
sudo systemctl status ssh.socket
```

```sh
ss -tulnp | grep 443
```


如果想同时监听 22 和 7890

在 /etc/ssh/sshd_config 里写：

Port 22
Port 7890

然后：

systemctl restart ssh
额外提醒（很重要）

在你确认 7890 能连接之前，建议保留 22：

Port 22
Port 7890


```sh
ufw delete deny 8090
```

Docker 默认会绕过 UFW


SSH 配置修改

```sh
# 监听
Port 22

# 连接稳定
TCPKeepAlive yes
ClientAliveInterval 60
ClientAliveCountMax 10

# DNS
UseDNS no

# 性能
Compression yes

# 限制
MaxAuthTries 3
MaxSessions 10

# 日志
SyslogFacility AUTH
LogLevel INFO
```


默认 ufw 无法管理 Docker，Docker 会绕过 ufw 直接操作 iptables
可以在 Docker 部署的时候端口，然后使用反代

```sh
# "8090:8090"
"127.0.0.1:8090:8090"
```

开启 bbr
BBR 在 高延迟链路

查看当前是否有 bbr 模块

```sh
modinfo tcp_bbr

# 加载 BBR 模块
modprobe tcp_bbr
# 查看支持的算法
sysctl net.ipv4.tcp_available_congestion_control
# 如果支持 BBR，则显示如下
# net.ipv4.tcp_available_congestion_control = reno cubic bbr

# 切换 BBR
sysctl -w net.core.default_qdisc=fq
sysctl -w net.ipv4.tcp_congestion_control=bbr
# 查看当前算法
sysctl net.ipv4.tcp_congestion_control
# 成功则显示
# net.ipv4.tcp_congestion_control = bbr

# 确认模块
lsmod | grep bbr
```

设置开启启动

```sh
echo "tcp_bbr" >> /etc/modules-load.d/bbr.conf
echo "net.core.default_qdisc=fq" >> /etc/sysctl.conf
echo "net.ipv4.tcp_congestion_control=bbr" >> /etc/sysctl.conf
sysctl -p
```

修改时区

```sh
timedatectl
timedatectl list-timezones
timedatectl set-timezone Asia/Shanghai
date

# 恢复默认
timedatectl set-timezone UTC
```