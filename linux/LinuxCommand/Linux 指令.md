在Unix和类Unix系统中，时间以秒来表示，从 1970 年 1 月 1 日 00:00:00 UTC 开始计算

```shell
sudo          # SuperUser Do 执行需要管理或超级用户权限的任务
exit          # 结束当前终端会话
su [username] # 切换用户

cd ..   # 上一级
cd /    # 根目录
cd ~    # 用户根目录
cd      # 用户根目录

./      # 当前目录下
../     # 上一级目录
../../  # 上上一级目录
~/      # 用户根目录
/       # 根目录

cp [file] [dir]              # 复制 [file] 文件到 [dir] 文件夹
cp [dir1] [dir2] -r          # 递归的复制 [dir1] 文件夹到 [dir2] 文件夹
mv [file] [dir]              # 移动 [file] 到文件夹 [dir] 文件夹
mv [file1] [file2]           # 重命名 [file1] 为 [file2] 文件夹
mkdir [dir]                  # 创建文件夹 [dir]
touch [file]                 # 创建文件 [file]
echo "hello world" > [file]  # 创建文件 [file]，并向文件内写入 "hello world"


pwd         # 显示当前工作文件夹的路径
ls          # 列出当前路径下的文件和文件夹
ls -l       # -l 选项查看当前路径下的文件和文件夹的详细信息
ls -la      # -a 选项查看所有文件
ls -laf     # -f 选项用于对结果进行排序
stat [file]	# 查看文件 [file] 的相关信息


rm [file]     # 删除指定文件
rm *.o        # 删除当前路径下所有后缀为 .o 的文件，其他后缀同理
rmdir [dir]   # 只能删除当前路径下的空文件夹 [dir]，非空无法删除
rm -r [dir]   # 删除指定文件夹

env           # 查看环境变量，坏境变量是键值对的形式，一个键可以对应多个值，中间用 “:” 分隔

[Ctrl][L]     # 隐藏之前输出内容
[Ctrl][C]     # 中断了进程，返回到终端界面
[Ctrl][Z]     # 暂停了进程，返回到终端界面

[Ctrl][Insert]      # 复制
[Ctrl][Shitf][C]    # 复制
[Shift][Insert]     # 粘贴
[Ctrl][Shift][V]    # 粘贴

[Ctrl][Shift][Up Arrow]    # 向上查看终端
[Ctrl][Shift][Down Arrow]  # 向下查看终端

alias graph="git log --graph --oneline --decorate --all" # 指令别名

umask       # 查看 umask
umask 0022  # 修改 umask 为 0022，只在当前终端有效

chsh -s /bin/[shell]  # 切换默认 shell

cat /etc/passwd	           # 查看所有用户信息
cat /etc/group	           # 查看所有组信息
sudo useradd [username]    # 新增用户
sudo passwd [username]     # 新用户创建密码
sudo userdel [username]    # 删除用户
sudo userdel -r [username] # 删除用户而不删除用户主目录
id [username]              # 查看 uid gid group

sudo service [servicename] start # 启动服务
sudo service [servicename] stop  # 结束服务

ulimit -a     # 显示目前资源限制的设定
ulimit [-op] v # 修改 op 资源大小为 v (当前终端)
# ulimit -c 1024

kill -l       # 列出系统中可用的信号列表
kill [pid]    # 终止指定进程
kill -9 [pid] # 强制终止指定进程进程，SIGKILL 信号来终止进程

./paragam &   # 后台运行程序

sudo shutdown [option] [time] [warningmessage]
sudo halt       # 系统停机，不断电
sudo poweroff   # 系统完全关闭
```

文件权限

```sh
drwxr-xr-x

d: 文件类型
# 每三个一组
rwx: 当前用户的权限
r-x: 当前用户所在的组的权限
r-x: 其他组的权限

# 二进制表示
1 111 101 101

# 八进制表示
1 7 5 5
```

### 命令帮助

`man` 查询命令 `command` 的说明文档

```sh
man [command]
```

man 文档有 9 个类别

1. 用户可以操作的命令或可执行文件
2. 系统核心可调用的函数与工具等
3. 一些常用的函数与数据库
4. 设备文件的说明
5. 设置文件或者某些文件的格式
6. 游戏
7. 惯例与协议等。例如 Linux 标准文件系统、网络协议、ASCII 说明内容
8. 系统管理员可用的管理条令
9. 与内核有关的文件

`whatis` 显示命令 `command` 所在的文档类别

```sh
whatis [command]
```

### 查看路径

查看程序所在路径

```sh
which [command]
```

查看程序的搜索路径

```sh
where [command]
```

查看程序的搜索路径

```sh
whereis [command]
```

