### MariaDB 安装

[MariaDB 官网](https://mariadb.com/kb/en/)


```sh
sudo pacman -S mariadb
```

安装后启动时遇到的错误：

```sh
$ sudo systemctl start mariadb 
Job for mariadb.service failed because the control process exited with error code.
See "systemctl status mariadb.service" and "journalctl -xeu mariadb.service" for details.
```

使用提示的命令查看日志：

```sh
journalctl -xeu mariadb.service
```

查看日志：

```sh
[ERROR] Can't open and lock privilege tables: Table 'm>
```

修复权限表：

```sh
sudo mysql_install_db --user=mysql --basedir=/usr --datadir=/var/lib/mysql

# --user=mysql 指定初始化数据库时使用的用户
# --basedir=/usr 指定 MariaDB 的安装基本目录
# --datadir=/var/lib/mysql 指定 MariaDB 数据目录
```

设置用户名及密码：

```sh
sudo mariadb -u root -p
```