[v2rayA wiki](https://v2raya.org/)

安装内核及 web gui 管理

```sh

yay -S v2raya-bin
```

启动服务

```sh
systemctl start v2raya.service
# 安装或更新后
systemctl restart v2raya.service
```

开机自启

```sh
systemctl enable v2raya.service
```

web gui `127.0.0.1:2017`