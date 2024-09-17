### Linux 安装

#### redis 安装

[github redis](https://github.com/redis/redis)

包管理器安装：

```sh
paru -S redis
```



#### hredis 安装

[github hredis](https://github.com/redis/hiredis)

源码安装：

```sh
git clone https://github.com/redis/hiredis
cd hredis
make
# PREFIX?=/usr/local
sudo make install
sudo ldconfig
```

#### 配置文件

`/etc/redis/redis.conf`

默认用户名 `default`

```sh
requirepass <password>
```

设置用户和密码：

```
user <default> on ><password> ~* +@all
```

redis 命令不区分大小写
