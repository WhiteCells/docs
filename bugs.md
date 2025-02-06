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
