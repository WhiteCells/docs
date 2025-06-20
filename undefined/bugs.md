在支持 IPv6 的系统中，`localhost` 优先解析为 `::1`（IPv6 回环地址），而不是 `127.0.0.1`（IPv4 回环地址）。

跨域请求（协议、主机名和端口）：

前端页面地址：`146.23.34.11:51515`

后端 API 地址：`146.23.34.11:43434`

就属于跨域请求。

预检请求（OPTIONS）

浏览器在发送实际请求之前，先发送 OPTIONS 请求，用于检测服务器是否允许请求

VirtualBox 中的增强功能，在安装后：

```sh
sudo mount /dev/cdrom /mnt
sudo sh /mnt/VBoxLinuxAdditions.run

sudo systemctl start vboxadd

reboot
```



go range 默认获取的是键

格式化输出 `%+v`



```sh
cat /etc/os-release
hostnamectl

lscpu
free -h
lsblk
df -h
```





当使用 python 使用 conda 的环境时，会可能找不到系统的环境变量：

```sh
export LD_LIBRARY_PATH=/usr/lib:$LD_LIBRARY_PATH
```





Linux sunlogin

```ssh
systemctl start runsunloginclient.service
```



VirtualBox Windwos 无法从无人参与应答文件读取<ProductKey> 设置

解决方法：在存储中将控制器下的软驱移除。

VirtualBox 格式转换

```sh
VBoxManage convertfromraw <image>.img <img>.vdi --format VDI
```



解决 `curl raw.githubusercontent.com` 速度慢问题：

```sh
echo "185.199.108.133 raw.githubusercontent.com" | sudo tee -a /etc/hosts
echo "185.199.109.133 raw.githubusercontent.com" | sudo tee -a /etc/hosts
echo "185.199.110.133 raw.githubusercontent.com" | sudo tee -a /etc/hosts
echo "185.199.111.133 raw.githubusercontent.com" | sudo tee -a /etc/hosts
```

vps 包管理器默认使用 IPv6，强制包管理器使用 IPv4：

```sh
echo 'Acquire::ForceIPv4 "true";' | sudo tee /etc/apt/apt.conf.d/99force-ipv4
```

或者禁用 IPv4（重启后失效）

```sh
sudo sysctl -w net.ipv6.conf.all.disable_ipv6=1
sudo sysctl -w net.ipv6.conf.default.disable_ipv6=1
sudo sysctl -w net.ipv6.conf.lo.disable_ipv6=1

# 启用
sudo sysctl -w net.ipv6.conf.all.disable_ipv6=0
sudo sysctl -w net.ipv6.conf.default.disable_ipv6=0
sudo sysctl -w net.ipv6.conf.lo.disable_ipv6=0
```





### bug

.service 会不断的重启服务（有参数时），占用端口
