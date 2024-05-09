PowerShell 终端代理修改

```sh
notepad $PROFILE
```

不存在则查看默认配置文件路径然后添加即可

```sh
$PROFILE
```

添加环境变量

```sh
# http
$Env:http_proxy = "<proxy-server-ip>:<port>"

# https
$Env:https_proxy = "<proxy-server-ip>:<port>"
```

或者带身份认证的代理

```sh
# http
$Env:http_proxy = "http://<username>:<password>@<proxy-server-ip>:<port>"

# https
$Env:https_proxy = "https://<username>:<password>@<proxy-server-ip>:<port>"
```

检验

```sh
curl cip.cc
```

CMD 终端代理修改，需要修改注册表

系统环境变量 `计算机\HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager\Environment`

用户环境变量 `计算机\HKEY_CURRENT_USER\Environment`

```cmd
# "HKEY_CURRENT_USER\Environment" 路径下添加（或修改）名为 "http_proxy" 和 "https_proxy" 的字符串值（REG_SZ）
reg add "HKCU\Environment" /v http_proxy /t REG_SZ /d http://proxyserver:port
reg add "HKCU\Environment" /v https_proxy /t REG_SZ /d https://proxyserver:port
```

或者在 Windows gui 的环境变量里设置，进行添加环境变量

检验

```sh
curl cip.cc
```

