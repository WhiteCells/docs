## GDB调试

GDB 是由 GNU 软件系统社区提供的调试工具，同 GCC 配套组成一套完整的开发环境，GDB 是 Linux 和许多类 Unix 系统中的标准开发环境。

### GDB 作用

1. 启动程序，可以按照自定义的要求随心所欲的运行程序
2. 可让被调试的程序在指定的断点处停住（断点可以是条件表达式）
3. 当程序停住时，可以检查此时程序中所发生的事
4. 可以改变程序，将一个 bug 所产生的影响修复，从而测试其他 bug

### GDB 准备

在为调试而编译时，关闭编译器的优化选项 `-o`，并打开调试选项 `-g`。另外，`-Wall` 在尽量不影响程序运行的情况下选择打开所有 warning，也可以发现许多问题。

```shell
gcc -g -Wall program.c -o program

# 
gcc program.c -o program -g
```

`-g`选项的作用是在可执行文件中加入源代码的信息，比如可执行文件中第几条机器指令对应源代码的第几行，但并不是将整个源文件嵌入可执行文件中，所以在调试时必须保证 gdb 能找到源文件。

```shell
# 比较 test（打开调试选项） 可执行文件和 test2（未打开调试选项） 可执行文件
xuan@ubuntu:~/Linux/gdb$ ll -h test test1
-rwxrwxr-x 1 xuan xuan  11K Jun 23 18:42 test*
-rwxrwxr-x 1 xuan xuan 8.3K Jun 23 18:43 test1*
```



### GDB 命令

- 启动和退出

  - ```shell
    gdb program # program 为可执行程序
    # # 进入 gdb 之后才能使用 gdb 命令
    ```

  - ```shell
    quit
    # 或
    q
    ```

- 给程序设置参数 / 获取设置参数

  - ```shell
    set args 10 20
    ```

  - ```shell
    show args
    ```

- 帮助

  - ```shell
    help
    ```

- 查看当前文件代码

  - ```shell
    list/l # 从默认位置显示，/ 或者
    ```

  - ```shell
    list/l row # row 为行，从指定的 row 行显示
    ```

  - ```shell
    list/l funcname # funcname 为函数名，从指定的函数 funcname 显示）
    ```

- 查看非当前文件代码

  - ```shell
    list/l filename:row # 查看 filename 文件中第 row 行
    ```

  - ```shell
    list/l filename:funcname # 查看 filename 文件中 funcname 函数
    ```

- 设置显示的行数

  - ```shell
    show list/listsize # 不能使用 l 简写
    ```

  - ```shell
    set list/listsize 行数 # 不能使用 l 简写
    ```

- 断点操作

  - 设置断点

    ```shell
    b/break row # 当前文件下 row 行处断点
    b/break funcname # 当前文件下 funcname 函数处断点
    b/break filename:row # filename 文件下 row 行处断点
    b/break filename:funcname # filename 文件下 funcname 断点
    ```

  - 查看断点

    ```shell
    i/info b/break
    
    (gdb) i b
    Num     Type           Disp Enb Address            What
    2       breakpoint     keep y   0x0000000000000bee in main() at main.cpp:10
    
    # Num 编号
    # Type 类型
    # Disp 
    # Enb 是 enable 缩写，该断点是否启用（y/n）
    # Address 断点地址
    # What 断点位置
    ```

  - 删除断点

    ```shell
    d/del/delete num # 删除编号 num 断点，可以同时删除多个断点，del 1 2 3
    ```

  - 设置断点无效

    ```shell
    dis/disable num # 无效编号 num 断点，可以同时无效多个断点
    ```

  - 设置断点生效

    ```shell
    ena/enable num # 编号 num 断点生效，可以同时生效多个节点 
    ```

  - 设置条件断点（一般用在循环的位置）

    ```shell
    b/break 10 if i==5
    ```


### GDB 使用

```shell
gdb program
# # 进入 gdb 之后才能使用 gdb 命令
```

给程序 main 函数传递参数

```shell
./program 10 20 # 给 program 可执行文件传递参数 10 20

# gdb 中
set args 10 20

# 结果
#(gdb) set args 10 20
#(gdb) show args
#Argument list to give program being debugged when it is started is "10 20"
```

### GDB 查看代码

```shell
list # 查看当前路径下的代码
# 或
l

# 一次只能查看 10 行
# 回车继续查看接下来的 10 行，继续使用上一次的命令
```

```shell
list row # 以 row 行为中间开始查看
```

```shell
list func # 以 func 函数作为中间开始查看
```

### GDB 调试命令

- 运行 GDB 程序

  ```sh
  start # 程序停在第一行
  run/r # 遇到断点才停
  ```

- 继续运行，到下一个断点停

  ```sh
  c/continue
  ```

- 向下执行一行代码，不进入函数体

  ```sh
  n/next
  ```

- 向下单步调试，进入函数体

  ```sh
  s/step
  finish # 跳出函数体
  ```

- 变量操作

  ```sh
  p/print 变量名 # 打印变量值
  ptype 变量名 # 打印变量类型
  ```

- 自动变量操作

  ```sh
  display 变量名 # 自动打印指定变量的值
  i/info display
  undisplay 编号
  ```

- 其他操作

  ```sh
  set var 变量名=变量值
  until # 跳出循环
  ```

### gdb 调试

#### gdb 指令

```sh
gdb -v # 查看当前 gdb 版本
```



#### 多线程调试

gdb program

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



```sh
run 			#运行程序，可简写为r
next 			#(可简写为n)单步跟踪，函数调用当作一条简单语句执行
step 			#(可简写为s)单步跟踪，函数调进入被调用函数体内
finish 			#退出进入的函数，若是你的函数里有断点，是不能退出的
until 			#(可简写为u)在一个循环体内单步跟踪时，这个命令可以运行程序直到退出循环体，即跳出当前(for)循环
continue 		#(可简写为c)继续运行程序
p j				#(print)查看j变量的值
ptype arr		#查看arr变量的类型
display j		#在循环中，每循环一次，就会把变量j的值打印出来，前提是j存在
i display		#查看你追踪变量的编号
undisplay 1		#取消编号为1的变量打印
set var i=10	#在运行时，设置变量i=10，就是设置变量的值
quit / q		#退出gdb调试
```

