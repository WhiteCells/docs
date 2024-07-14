## Makefile

- 工程中的源文件按类型、功能、模板分别放在若干个目录中，Makefile 文件定义了一系列的规则来指定哪些文件需要先编译，哪些文件需要后编译，哪些文件需要重新编译，甚至进行一些更复杂的操作，Makefile 文件就像 Shell 脚本一样，也可以执行操作系统的命令。

- Makefile 带来的好处是 “自动化编译”，一旦写好，只需要一个 make 命令，整个工程完全自动编译，极大的提高了软件开发的效率。make 是一个命令工具，是一个解释 Makefile 文件中指令的命令工具，一般来说，大多数的 IDE 都有这个命令，Delphi 的 make，Visual C++ 的 nmake，Linux 下 GNU 的 make。

- 命名规则

  - makefile 或 Makefile

- makefile 规则

  - 一个 makefile 文件中可以有一个或多个规则

    - ```makefile
      目标 ...:依赖 ...
      	命令(Shell 命令)
      	...
      	
      # 目标 最终生成都文件（伪目标除外）
      # 依赖 生成目标所需要的文件或是目标
      # 命令 通过执行命令对依赖操作生成目标（命令前必须 tab 缩进）
      ```

  - makefile 中的其他规则一般都是为第一条规则服务的

### makefile 基础使用

创建并编辑 Makefile 文件

```shell
vim Makefile
# vim makefile
```

测试项目树

```shell
.
├── add.c
├── div.c
├── head.h
├── main.c
├── mult.c
└── sub.c
```

Makefile 文件编辑

```makefile
app:add.c sub.c mult.c div.c main.c
        gcc add.c sub.c mult.c div.c main.c -o app
```

make 指令

```shell
make
# apt install make
# make 会在当前路径下找 Makefile 文件
```

### makefile 工作方式

- 命令在执行之前，需要先检查规则中的依赖是否存在
  - 如果存在，执行命令
  - 如果不存在，向下检查其他的规则，检查有没有一个规则是用来生成当前这个依赖的，如果找到了，则执行该规则中的指令
- 检查更新，在执行规则中的命令时，会比较目标和依赖文件的时间
  - 如果依赖的时间比目标的时间晚，需要重新生成目标
  - 如果依赖的时间比目标的时间早，目标不需要更新，对应规则中的命令不需要被执行



1、依赖如果不存在，向下检查其他的规则，检查有没有一个规则是用来生成当前这个依赖的，如果找到了，则执行该规则中的指令

```makefile
app:main.o add.o sub.o mult.o div.o # main.o add.o sub.o mult.o div.o 这些依赖需要在下面的规则中去找
        gcc main.o add.o sub.o mult.o div.o -o app

main.o:main.c # main.o 目标文件，依赖于 main.c 文件
        gcc -c main.c

add.o:add.c
        gcc -c add.c

sub.o:sub.c
        gcc -c sub.c

mult.o:mult.c
        gcc -c mult.c

div.o:div.c
        gcc -c div.c
```

make 指令运行

```shell
xuan@ubuntu:~/Linux/makefile$ make
gcc -c main.c # 先对 .c 文件进行汇编，生成 .o 文件
gcc -c add.c
gcc -c sub.c
gcc -c mult.c
gcc -c div.c
gcc main.o add.o sub.o mult.o div.o -o app # 再对 .o 文件进行链接，生成 app 可执行文件
```

2、检查更新，在执行规则中的命令时，会比较目标和依赖文件的时间

当不更新源文件（依赖未修改，依赖比目标早），再次执行 make 命令

```shell
xuan@ubuntu:~/Linux/makefile$ make
make: 'app' is up to date. # app 已是最新
```

当对 main.c 文件稍作修改（依赖修改，依赖比目标晚），再次执行 make 命令

```shell
xuan@ubuntu:~/Linux/makefile$ make
gcc -c main.c # 重新汇编 main.c 文件，重新生成新的 main.o 目标文件
gcc main.o add.o sub.o mult.o div.o -o app
```

### makefile 变量使用

- 自定义变量

变量名 = 变量值

```makefile
var = value
```

- 预定义变量

```makefile
AR # 递归维护程序的名称，默认值为 ar

CC # 编译器的名称，默认为 cc

CXX # c++ 编译器的名称，默认为 g++

$@ # 获取目标的完整名称（当前规则下）

$< # 获取第一个依赖文件的名称（当前规则下）

$^ # 获取所有依赖文件（当前规则下）
```

- 获取变量的值

```makefile
$(变量名)

# 例如获取 CXX
$(CXX)
```

makefile 文件重新编辑

```makefile
src=main.o add.o sub.o mult.o div.o
target=app

$(target):$(src)
		$(CC) $(src) -o $@

main.o:main.c
		$(CC) -c $< -o $@

add.o:add.c
		$(CC) -c $< -o $@

sub.o:sub.c
		$(CC) -c $< -o $@

mult.o:mult.c
		$(CC) -c $< -o $@

div.o:div.c
		$(CC) -c $< -o $@
```



### makefile 模式匹配

```makefile
%.o:%.c
# % 为通配符，这两个 % 代表的是统一个字符串
```

例如

```makefile
%.o:%.c
		$(CC) -c $< -o $@ # $< 获取到的是依赖 %.c
```

makefile 文件重新编辑

```makefile
src=main.o add.o sub.o mult.o div.o
target=app

$(target):$(src)
		$(CC) $(src) -o $@

%.o:%.c
		$(CC) -c $< -o $@
```

### makefile 函数使用

$(wildcard PATTERN...) 

- 功能：指定目录下指定类型的文件列表
- 参数 PATTERN：是某个或多个目录下的对应的某种类型的文件，如果有多个目录，一般使用空格间隔
- 返回：若干个文件的文件列表，文件之间用空格间隔

文件树

```
.
├── app
├── include
│   └── head.h
├── lib
│   └── libcal.so
├── main.c
└── src
    ├── add.h
    ├── div.c
    ├── mult.c
    └── sub.c
```

使用函数获取 .c 文件名

```makefile
$(wildcard ./*.c ./src/*.c)
# 返回当前路径下和上一级路径下的所有 .c 文件
# 返回 main.c add.c sub.c mult.c div.c
```

$(patsubst \<patter\>, \<replacement\>, \<text\>)

- 功能：查看 <text> 中的单词（单词以空格、tab、回车、换行 进行分隔）是否符合模式 <pattern>，如果匹配的话，则以 <replacement> 替换。
- <pattern> 可以包括通配符 %，表示任意长度的字符串。如果 <replacemet> 中也包含 %，那么，<replacement> 中的这个 % 将是 <pattern> 中的那个 % 所代表的字符串。（\% 表示字符 %，% 表示通配符）
- 返回：函数返回被替换过后的字符串

使用函数将 .c 文件替换为 .o 文件

```makefile
$(patsubet %.c, %.o, $(src))
# 返回 main.o add.o sub.o mult.o div.o
```

makefile 文件重新编辑

```makefile
src=$(wildcard ./*.c)
objs=$(patsubst %.c, %.o, $(src))
target=app

$(target):$(objs)
        $(CC) $(objs) -o $@

%.o:%.c
        $(CC) -c $< -o $@
```

删除生成的 .o 文件，添加以下内容

```makefile
clean:
		rm $(objs) -f
```

执行 `make clean`，就可以删除 .o 文件，需要单独执行是因为 makefile 只会执行第一条规则和与其相关的依赖，clean 不是相关依赖，所以想要执行 clean 规则，必须单独执行。

但是如果有 clean 文件，`make clean` clean 规则会生成目标文件（目标文件相对于依赖文件更晚一些），再次执行 `make clean`，就会提示 `make: 'clean' is up to date.`

```makefile
.PTONY:clean # 表示 clean 是一个伪目标，不生成特定文件
clean:
		rm $(objs) -f
```

再次执行 `make clean` 可以删除 .o 文件
