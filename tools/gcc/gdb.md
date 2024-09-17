### GDB 准备

在为调试而编译时，打开调试 `-g`，关闭编译器的优化 `-O0`，打开所有推荐的警告信息 `-Wall`

```shell
gcc program.c -g -Wall -O0 -o program
```

`-g `选项的作用是在可执行文件中加入源代码的信息，比如可执行文件中第几条机器指令对应源代码的第几行，但并不是将整个源文件嵌入可执行文件中，所以在调试时必须保证 gdb 能找到源文件。

```shell
# program1（打开调试选项） 可执行文件和 program2（未打开调试选项） 可执行文件
-rwxrwxr-x 1 xxx xxx  11K Jun 23 18:42 program1*
-rwxrwxr-x 1 xxx xxx 8.3K Jun 23 18:43 program2*
```

### GDB 命令

启动和退出

```sh
# 启动
gdb program

# 退出
quit
q
```

程序参数

```sh
# 设置参数
set args 10 20

# 显示参数
show args
```

帮助

```shell
help
```

查看代码

```shell
# 从默认位置显示或继续向下显示
list
l

# <row> 为行，从指定的 <row> 行显示
list <row>
l <row>

# 从指定的函数 <func>
list <func>
l <func>

# 查看 <file> 文件中第 <row> 行
list <file>:<row>
l <file>:<row>

# 查看 <file> 文件中 <func> 函数
list <file>:<func>
l <file>:<func>

# 设置显示的行数 <row>
set listsize <row>
set list <row>

# 显示每一次显示的行数
show listsize
show list
```

断点操作

```shell
# 设置当前文件下 <row> 行断点
break <row>
b <row>

# 设置当前文件下 <func> 函数断点
break <func>
b <func>

# 设置 <file> 文件下 <row> 行断点
break <file>:<row>
b <file>:<row>

# 设置 <file> 文件下 <func> 函数断点
break <file>:<func>
b <file>:<func>
```

查看断点

```shell
i/info b/break

(gdb) i b
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x0000000000000bee in main() at main.cpp:10

# Num    断点编号
# Type   断点类型 breakpoint、watchpoint或catchpoint
# Disp   处理方式 keep或del
# Enb 是 enable 缩写，该断点是否启用 y或n
# Address 断点地址
# What    断点位置
```

删除断点

```shell
# 删除编号 num 断点，可以同时删除多个断点，del 1 2 3
delete <num>
del <num>
d <num>
```

设置断点无效

```shell
# 无效编号 num 断点，可以同时无效多个断点
disable <num>
dis <num>
```

设置断点生效

```shell
# 编号 num 断点生效，可以同时生效多个节点
enable <num>
ena <num>
```

设置条件断点

```shell
break 10 if i==5
b 10 if i==5
```

### GDB 调试命令

运行 GDB 程序

```sh
# 停在第一行
start

# 断点停
run
r
```

继续运行，到下一个断点停

```sh
# 下一个断点
continue
c
```

执行下一行代码，不进入函数体

```sh
# 下一行，不进入函数
next
n
```

向下单步调试，进入函数体

```sh
# 下一行，进入函数
step
s

# 跳出函数体
finish

# 跳出循环
until
```

变量操作

```sh
# 打印变量值 <var>
print <var>
p <var>

# 打印变量 <var> 类型
ptype <var>
```

自动变量操作

```sh
# 设置自动打印变量 <var> 的值
display <var>

# 列出自动打印变量
info display
i display

# 关闭自动打印编号为 <num> 的变量的值
undisplay <num>
```

变量设置值

```sh
# 变量 <var1> 设置值 <val1>
set var <var1>=<val1>
```

### GDB 多线程调试

gdb 默认跟踪父进程

```sh
show follow-fork-mode # 显示 follow-fork-mode
show detach-nofork # 查看调试模式
set follow-fork-mode [parent(默认) | child] # 设置调试父进程或子进程
set detach-no-fork [no(默认) | off] # 设置调试模式，no 表示调试当前进程时，其他进程继续运行，脱离 gdb 调试，off 表示其他进程被 gdb 挂起在 fork 函数位置

info inferiors # 查看调试的进度
i i

inferior id # 切换当前调试的进度
detach inferiors id # 使进程脱离 gdb 调试
```

