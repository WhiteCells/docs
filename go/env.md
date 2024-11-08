### SDK（Software Development Kit）

https://go.dev/

https://studygolang.com/pkgdoc

https://pkg.go.dev/std



### Linux 配置 go 环境

```sh
wget https://go.dev/dl/go1.23.2.linux-amd64.tar.gz # 1.23.2

sudo tar -C /usr/local -xzf go1.23.2.linux-amd64.tar.gz
```

编辑 `~/.profile` 文件，添加以下内容：

```sh
export PATH=$PATH:/usr/local/go/bin
```

使更改生效：

```sh
source ~/.profile
```



### Windows 配置 go 环境

https://go.dev/dl/

将 `bin` 文件夹添加到系统 `PATH`

