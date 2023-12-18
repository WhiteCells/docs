Windows 操作

```shell
# 在本机生成 ssh 公钥和私钥，已经存在则不需要生成
ssh-keygen -t rsa

# 复制公钥到剪切板
type C:\Users\[Name]\.ssh\id_rsa.pub | clip
```

Linux 操作

```shell
# Linux 里也生成公钥和私钥
ssh-keygen -t rsa
# 路径下创建一个文件 authorized_keys
# 将公钥内容复制该文件
vim ~/.ssh/authorized_keys
```

