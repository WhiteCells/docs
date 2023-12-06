在本机生成 ssh 公钥

```shell
ssh-keygen -t rsa
```

生成到本机用户名下的 `.ssh` 的 id_rsa.pub

将公钥发送到 Ubuntu，Ubuntu 里也生成公钥和私钥，

在 Ubuntu 中 .ssh 路径下创建一个文件 **authorized_keys**

```shell
cd .ssh/
vim authorized_keys
```

把本机生成的公钥复制进去，之后在 vscode 连接 Ubuntu 就不需要每次输入密码

