### error001

#### ssh: Could not resolve hostname ssh.github.com: Temporary failure in name resolution fatal: Could not read from remote repository.

```sh
ssh: Could not resolve hostname ssh.github.com: Temporary failure in name resolution
fatal: Could not read from remote repository.

Please make sure you have the correct access rights
and the repository exists.
```

关闭代理

### error002

#### Using 'master' as the name for the initial branch. This default branch name

初始化仓库时出现以下错误：

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

全局修改默认初始化分支为 main

```sh
git config --global init.defaultBranch main # 直接全局修改默认初始化分支为 main

# 也可以在该仓库中单独设置分支
git branch -m main
```

### error003

#### ssh: connect to host github.com port 22: Connection refused

配置好 ssh 后测试 `ssh -T git@github.com`

```sh
ssh: connect to host github.com port 22: Connection refused
```

Linux 解决方法：

```sh
vim ~/.ssh/config
```

写入以下内容，修改 ssh 连接时使用的端口

```
Host github.com
  Hostname ssh.github.com
  Port 443
```

Windows 解决方法：

在 `C:\Users\User\.ssh` 中添加以下内容：

```
Host github.com
User [email]
Hostname ssh.github.com
PreferredAuthentications publickey
IdentityFile ~/.ssh/id_rsa
Port 443
```

### error004

#### fatal: not a git repository (or any of the parent directories): .git

问题描述:

在初始化过本地仓库，有远程仓库的前提下，且配置好了 ssh，连接远程仓库出现报错

```sh
fatal: not a git repository (or any of the parent directories): .git
```

重新初始化仓库

```sh
git init
```

### error005

#### The authenticity of host 'ssh.github.com (20.205.243.160)' can't be established.

```sh
ECDSA key fingerprint is SHA256:p2QAMXNIC1TJYWeIOttrVc98/R1BUFWu3/LiyKgUfQM.
Are you sure you want to continue connecting (yes/no/[fingerprint])?
```

直接输入 yes 回车即可

