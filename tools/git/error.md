### error001

```sh
ssh: Could not resolve hostname ssh.github.com: Temporary failure in name resolution
fatal: Could not read from remote repository.

Please make sure you have the correct access rights
and the repository exists.
```

解决方法：

关闭代理

### error002

```sh
hint: Using 'master' as the name for the initial branch. This default branch name
hint: is subject to change. To configure the initial branch name to use in all
hint: of your new repositories, which will suppress this warning, call:
hint: 
hint:   git config --global init.defaultBranch <name>
hint: 
hint: Names commonly chosen instead of 'master' are 'main', 'trunk' and
hint: 'development'. The just-created branch can be renamed via this command:
hint: 
hint:   git branch -m <name>
```

初始化仓库时出现错误

解决方法：

全局修改默认初始化分支为 main

```sh
git config --global init.defaultBranch main # 直接全局修改默认初始化分支为 main

# 也可以在该仓库中单独设置分支，需要在由提交
git branch -m main
```

### error003

```sh
ssh: connect to host github.com port 22: Connection refused
```

解决方法：

```sh
# Linux
vim ~/.ssh/config

# Windows
notepad C:\Users\[Username]\.ssh\config
```

写入以下内容，修改 ssh 连接时使用的端口

```sh
# 使用 22 端口
# Host github.com
#   Hostname github.com
#   User git
#   Port 22
#   IdentityFile ~/.ssh/your_private_key

# 使用 443 端口
# 用于 HTTPS 流量，有助于绕过防火墙或网络限制
Host github.com
  Hostname ssh.github.com
  User git
  Port 443
  IdentityFile ~/.ssh/your_private_key

# 指定首选的身份验证方法
  PreferredAuthentications publickey
```

```sh
# 测试SSH连接
ssh -T -p 443 git@ssh.github.com
ssh -T -p 22 git@github.com
# 默认端口号 22
ssh -T git@github.com 
```

### error004

```sh
fatal: not a git repository (or any of the parent directories): .git
```

在初始化过本地仓库，有远程仓库的前提下，且配置好了 ssh，连接远程仓库出现报错

解决方法：

重新初始化仓库

```sh
git init
```

### error005

The authenticity of host 'ssh.github.com (20.205.243.160)' can't be established.

```sh
ECDSA key fingerprint is SHA256:p2QAMXNIC1TJYWeIOttrVc98/R1BUFWu3/LiyKgUfQM.
Are you sure you want to continue connecting (yes/no/[fingerprint])?
```

直接输入 yes 回车即可

### error006

```sh
warning: ----------------- SECURITY WARNING ----------------
warning: | TLS certificate verification has been disabled! |
warning: ---------------------------------------------------
warning: HTTPS connections may not be secure. See https://aka.ms/gcm/tlsverify for more information.
warning: ----------------- SECURITY WARNING ----------------
warning: | TLS certificate verification has been disabled! |
warning: ---------------------------------------------------
warning: HTTPS connections may not be secure. See https://aka.ms/gcm/tlsverify for more information.
```

https 方式连接远程仓库时出现报错

解决方法：

```sh
git config --global http.sslVerify true
```

### error007

```sh
fatal: detected dubious ownership in repository at 'D:/distake/code'
'D:/distake/code' is owned by:
        'S-1-5-32-544'
but the current user is:
        'S-1-5-21-3863718942-992295975-852214126-1001'
To add an exception for this directory, call:

        git config --global --add safe.directory D:/distake/code
```

解决方法：

```sh
git config --global --add safe.directory "*"
```

> ```cmd
> # 当前用户的详细信息，所属用户组和权限
> whoami /all
> ```
>

### error008

```sh
ERROR: Permission to weelen/web.git denied to WhiteCells.
fatal: Could not read from remote repository.

Please make sure you have the correct access rights
and the repository exists.
```

解决方法：

```sh
# 生成新的密钥（别名），将密钥添加到 github SSH keys
ssh-keygen -f id_rsa_github_weelen

# 修改 config 文件
Host github.com
Hostname ssh.github.com
PreferredAuthentications publickey
IdentityFile ~/.ssh/id_rsa_github
Port 443

# 新增
Host github2
Hostname ssh.github.com
PreferredAuthentications publickey
IdentityFile ~/.ssh/id_rsa_github_weelen
Port 443

# 修改远程仓库地址
git remote set-url origin git@github2:weelen/web.git
# git remote add origin git@github2:weelen/web.git

# 为仓库设置局部用户名和邮箱，建议填写真实邮箱，Commits 记录
git config user.name weelen
git config user.email xxxxx@gmail.com
```

