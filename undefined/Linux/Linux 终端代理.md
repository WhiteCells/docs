查看当前使用的 shell

```sh
echo $SHELL
# or
ps -p $$
# or
echo $0
```

编辑对应的 shell 的 rc（run command）文件

```sh
# bash
vim ~/.bashrc

# zsh
vim ~/.zshrc
```

加入环境变量

```sh
# http
export http_proxy="<proxy-server-ip>:<port>"

# https
export https_proxy="<proxy-server-ip>:<port>"
```

或者带身份认证的代理

```sh
# Proxy with authentication
# http
export http_proxy="http://<username>:<password>@<proxy-server-ip>:<port>"

# https
export https_proxy="https://<username>:<password>@<proxy-server-ip>:<port>"
```

暂时取消代理

```sh
unset http_proxy
unset https_proxy
```

检验

```sh
curl cip.cc
```

