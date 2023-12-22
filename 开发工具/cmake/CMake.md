### CMake Features

CMake 是一个开源的、跨平台的自动化构建工具

1. 跨平台：可以在多种操作系统上运行
2. 生成多种构建系统的文件：可以生成多种构建系统的构建文件，包括 Unix Makefiles、Ninja、MSVC 项目文件等
3. 支持大项目：支持多个目标（例如库和可执行文件），可以处理复杂的依赖关系
4. 寻找和使用库：可以寻找和使用各种库
5. 可拓展性：语法灵活、可以通过自定义函数和宏来扩展功能
6. 测试支持：包含 CTest，用于测试的工具，可以添加和运行项目测试
7. 打包支持：包含 CPack，用于生成分发包的工具，可以生成各种格式的分发包，包括 tar.gz、deb、rpm、dmg、nsis 等



```cmake
# CMakeLists.txt
cmake_minimum_required(VERSION 3.20) # 最低版本要求
project(project-name) # 项目名
add_executable(project-name main.cpp) # 由源文件生成一个可执行的程序
```

```sh
cmake -B build # 创建一个 build 目录并在此目录下生成构建文件
cmake --build build # 构建项目

cmake -P *.cmake # 执行文件

cmake -G "[generator-name]" -T [toolset-spec] -A [platform-name] -B [path-to-source]
```

### Windows CMake

[CMake installation](https://cmake.org/download/)

```cmake
# 生成构建文件
# 默认生成 MSVC 构建文件
# cmake -h 查看可生成构建文件
cmake -G "[generator-name]" -T [toolset-spec] -A [platform-name] -B [path-to-source]
# cmake -B [build]
# cmake -G "MinGW Makefiles" -B [linux-build]

# 构建项目
cmake --build [build]
```

### Linux CMake

```sh
# 包安装
sudo apt install cmake

# 源码编译
# 安装编译工具
sudo apt install build-essential
# 下载源码
sudo wget https://cmake.org/files/v3.28/cmake-3.28.0.tar.gz
# 解压源码
tar -zxvf cmake-3.28.0.tar.gz
cd cmake-3.28.0
# 配置编译参数
./configure
# 编译
sudo make
# 安装
sudo make install
# 检查是否安装成功
cmake --version
```

### CMake Syntax

#### message

```cmake
# synatx.cmake
message("hello world")
message("hello 
world")
message(hello\ world)
message(hello\ 
world)
message([[hello world]])
message([[hello 
world]])
message([[hello world]])
message([[hello 
world]])

# 执行 cmake 文件
# $cmake -P synatx.cmake
# hello world
# hello 
# world
# hello world
# hello world
# hello world
# hello 
# world
# hello world
# hello 
# world
```

#### set

```cmake
# 变量名有两种，CMake 提供、自定义
# 变量名区分大小写
# 变量名不能包含空格
# 变量名不能以数字开头
# 避免使用 CMake 关键字
# 变量存储时都是字符串

# ${[var_name]} # 获取变量 
message(${CMAKE_VERSION})

# set
set(var1 "test variable")
set(var2 [[test variable]])
set(var3 test\ variable)

message(${var1} " " ${var2} " " ${var3})

# list
set(list1 a b)
set(list2 a;b)
message(${list1} " " ${list2})

# $PATH
message($ENV{PATH})
set(ENV{CXX} "g++")
message($ENV{CXX})

# unset
unset(ENV{CXX})
# message($ENV{CXX}) # 不存在则报错
```

#### list

```cmake
# list
# list(APPEND  [list] [ele])      
# list(REMOVE  [list] [rm_ele])       
# list(LENGTH  [list] [out_var])      
# list(FIND    [list] [val] [out_var])  
# list(INSERT  [list] [index] [ele])  
# list(REVERSE [list])               
# list(SORT    [list] [...])            

set(PORT a1; a2; a3)

# APPEND
list(APPEND PORT p1 p2 p3)
message(${PORT})

# REMOVE
list(REMOVE_ITEM PORT a1)
message(${PORT})

# LENGTH
list(LENGTH PORT PORT_LEN)
message(${PORT_LEN})

# FIND
list(FIND PORT a1 idx)
message(${idx}) # -1 表示不存在
list(FIND PORT a2 idx)
message(${idx}) # 下标从 0 开始

# INSERT
list(INSERT PORT 0 a1)
message(${PORT})

# REVERSE
list(REVERSE PORT)
message(${PORT})

# SORT
list(SORT PORT)
message(${PORT})
```

#### control flow

```cmake
# if

# 数值比较
# LESS
# GREATER
# EQUAL
# LESS_EQUAL
# GREATER_EQUAL

# 字符串比较
# STREQUAL
# ...

if(${CMAKE_VERSION} LESS 3.28.0)
    message("version too low")
elseif(${CMAKE_VERSION} EQUAL 3.28.0)
    message("version correct")
else()
    message("version too high")
endif()

if(1 EQUAL "1")
    message("equal") # equal
else()
    message("not equal")
endif()


# foreach

# foreach([loop_var] [max])
foreach(var RANGE 3) # [0, 3]
    message(${var})
endforeach()

## foreach([loop_var] RANGE [min] [max] [step])
foreach(var RANGE 0 4 2)
    message(${var})
endforeach()

set(list1 var1 var2 var3 var4)
set(list2 VAR1 VAR2 VAR3)

## foreach([loop_var] IN [LISTS lists] [ITEMS items])
foreach(var IN LISTS list1 list2 ITEMS new_var1 new_var2)
    message(${var})
endforeach()

## foreach([loop_var] IN ZIP_LISTS [lists])
foreach(var IN ZIP_LISTS list1 list2)
    message("list1 = "${var_0} " list2 = " ${var_1})
endforeach()


# while

set(counter 10)
while (counter GREATER_EQUAL 0)
    message(${counter})
    math(EXPR counter "${counter} - 3")
endwhile()
```

#### function

```cmake
# function
## function([fun_name] [arguments])
## endfunction()

function(foo arg1 arg2)
    message(${CMAKE_CURRENT_FUNCTION},${arg1}, ${arg2})
    message(${ARGV0},${ARGV1})
    set(arg1 2) # 修改
    message("arg1: " ${arg1}) # 2
endfunction()

set(arg1 1)
foo(${arg1} 2)
message("arg1: " ${arg1}) # 1

function(foo2 arguments)
    message(${CMAKE_CURRENT_FUNCTION}, ${arguments})
    message(${ARGV0}, ${ARGV1})
endfunction()

foo2("arg1" "arg2")

function(foo3)
    message(${ARGV0}, ${ARGV1})
endfunction()

foo3(a1 a2)

# function scope
function(Func1)
    message("-> Func1 var: " ${var}) # 1
    set(var 2)
    Func2()
    message("<- Func1 var: " ${var}) # 2
endfunction()

function(Func2)
    message("-> Func2 var: " ${var}) # 2
    set(var 3)
    message("<- Func2 var: " ${var}) # 3
endfunction()

set(var 1)
Func1(var)
message("var: "${var})
```

#### macro

```cmake
# macro
# marco([name] [arguments])
# endmacro()

macro(Test arg)
    set(val "new value")
    message(${arg})
endmacro()

set(val "val")
message(${val}) # val
Test("test arg")
# replace
## set(val "new value")
## message("test arg")
message(${val}) # new val
```

---

add_executable 写入相对路径，在中引入头文件需要相对路径

