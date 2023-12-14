### error001

#### Failed to connect to raw.githubusercontent.com port 443: Connection refused

https://www.ipaddress.com/ 查询一下 raw.githubusercontent.com 对应的IP 地址

修改 hosts 文件

```sh
sudo vim /etc/hosts
```

添加

```
185.199.108.133 raw.githubusercontent.com
```



### error002

更新失败问题

```
echo "nameserver 8.8.8.8" | sudo tee /etc/resolv.conf
```

