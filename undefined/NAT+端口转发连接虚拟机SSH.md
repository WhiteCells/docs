虚拟机以 NAT 方式连接，端口转发

| 协议 | 主机 IP             | 主机端口 | 子系统 IP                | 子系统端口         |
| ---- | ------------------- | -------- | ------------------------ | ------------------ |
| TCP  | 127.0.0.1（可留空） | 2222     | 10.0.2.15（NAT 默认 IP） | 22（SSH 默认端口） |

主机 SSH 连接：

```sh
ssh -p 2222 root@127.0.0.1
```



SSH 连接时，可以将 root 允许连接打开：

```sh
vim /etc/ssh/sshd_config
# 修改
PermitRootLogin yes
# Password
# BindAddress
```

