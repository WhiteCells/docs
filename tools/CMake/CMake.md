### CMake Features

[CMake](https://github.com/Kitware/CMake) 是一个开源的、跨平台的自动化构建工具

1. 跨平台：可以在多种操作系统上运行
2. 生成多种构建系统的文件：可以生成多种构建系统的构建文件，包括 Unix Makefiles、Ninja、MSVC 项目文件等
3. 支持大项目：支持多个目标（例如库和可执行文件），可以处理复杂的依赖关系
4. 寻找和使用库：可以寻找和使用各种库
5. 可拓展性：语法灵活、可以通过自定义函数和宏来扩展功能
6. 测试支持：包含 CTest，用于测试的工具，可以添加和运行项目测试
7. 打包支持：包含 CPack，用于生成分发包的工具，可以生成各种格式的分发包，包括 tar.gz、deb、rpm、dmg、nsis 等

```cmake
## CMakeLists.txt

## 指定所需的 CMake 最低版本号
cmake_minimum_required(VERSION 3.20)

## 指定项目的名称、版本号和描述信息
## project(<项目名称> [VERSION <版本号>] [DESCRIPTION <描述>] [HOMEPAGE_URL <主页URL>] [LANGUAGES <语言1> <语言2> ...])
project(project-name CXX)

## 指定 C++ 标准
set(CMAKE_CXX_STANDARD 11)

## 严格遵守指定的 C++ 标准
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# 指定的 CMake 脚本文件包含到当前的 CMakeLists.txt 文件中进行处理
include(test.cmake)

## 生成配置文件
## 将 config.h.in 中的变量替换为 CMake 中定义的值，并将结果输出到 config.h 文件中
configure_file(config.h.in config.h)

## 定义目标（可执行文件或库）的名称，指定源文件列表
add_executable(app main.cpp)

## 添加将子目录到构建中，并处理该目录的 CMakeLists.txt 文件
add_subdirectory(${PROJECT_SOURCE_DIR}/src)

## 为所有目标指定头文件搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)

## 指定目标所依赖的库文件或目标文件
target_link_libraries(app PUBLIC testlib)

## 为特定目标指定头文件搜索路径
target_include_directories(app PUBLIC ${PROJECT_BINARY_DIR})

## 将指定宏定义添加到目标的编译定义中
target_compile_definitions(libtest PUBLIC "USE_TEST1")

## 指定链接器在链接过程中搜索库文件的目录
link_directories(${PROJECT_SOURCE_DIR}/lib)

## 将指定库链接到当前目标
link_libraries(libtest)

# 将指定目录 <directory> 下的所有源文件添加到指定变量 <variable> 中
aux_source_directory(<directory> <variable>)

### 文件搜索
## 根据指定的通配符模式获取文件列表，并将结果存储到变量中
file(GLOB SRC ${PROJECT_SOURCE_DIR}/src/*.cpp)

## 设置可执行文件的输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

### 静态库和动态库
## 设置库的输出路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/dll)
## 创建一个动态库到指定路径，将指定源文件添加到该库中
add_library(libtest SHARED ${SRC})
## 创建一个静态库到指定路径，将指定源文件添加到该库中
add_library(libtest STATIC ${SRC})
## add_library 默认为静态库
## add_library(libtest ${SRC})

### 作用域
# PUBLIC 本目标需要，依赖于本目标的其他目标也需要
# INTERFACE 本目标不需要，依赖于本目标的其他目标需要
# PRIVATE 本目标需要，依赖于本目标的其他目标不需要
```

### Command

```sh
## 查看可生成构建文件
cmake -h

cmake -G "[generator-name]" -T [toolset-spec] -A [platform-name] -B [path-to-source]

## 创建一个 build 目录并在此目录下生成构建文件
cmake -B build

## 构建文件生成之后，修改源文件后只需要使用构建文件进行构建即可
## 以 build 目录下的文件构建项目
cmake --build build

## 执行名为 test 的 CMake 文件
cmake -P test.cmake
```

### CMake Syntax

#### built-in variables

```cmake
CMAKE_CXX_STANDARD
# 指定 C++ 标准

CMAKE_CXX_STANDARD_REUQUIRED
# 为 ON 时（默认），如果指定的 C++ 标准编译器不支持，则 CMake 配置失败
# 为 OFF 时，CMake 将寻找编译器支持的最近的标准

CMAKE_CXX_EXTENSIONS
# 开启或关闭编译器指定的拓展

PROJECT_NAME
PROJECT_VERSION
PROJECT_IS_TOP_LEVEL
PROJECT_LABEL
PROJECT_SOURCE_DIR
PROJECT_BINARY_DIR
```



#### message

```cmake
message("hello world")
# hello world

message("hello 
world")
# hello
# world

message(hello\ world)
# hello world

message(hello\ 
world)
# hello
# world

message([[hello world]])
# hello world

message([[hello 
world]])
# hello
# world

message(STATUS "to do")
# -- to do

message(FATAL_ERROR "error message")
# CMake Error at test.cmake:25 (message):
#   error message
```

#### set

```cmake
# 变量名有两种，CMake 内置、自定义
# 变量名区分大小写
# 变量名不能包含空格
# 变量名不能以数字开头
# 避免使用关键字和内置变量
# 变量存储时都是字符串

# ${var_name} # 获取变量
# 内置变量并不都是有初始值的
message(${CMAKE_VERSION})            # 当前 CMake 的版本号
message(${CMAKE_SOURCE_DIR})         # 顶级源代码目录的路径
message(${CMAKE_BINARY_DIR})         # 顶层构建目录的路径
message(${CMAKE_CURRENT_SOURCE_DIR}) # 当前处理的 CMakeLists.txt 文件所在的源代码目录的路径
message(${CMAKE_CURRENT_BINARY_DIR}) # 当前处理的 CMakeLists.txt 文件所在的构建目录的路径
message(${CMAKE_CURRENT_LIST_FILE})  # 当前处理的 CMakeLists.txt 文件的完整路径，包括文件名
message(${CMAKE_MODULE_PATH})        # 指定额外的模块查找路径的列表
message(${CMAKE_BUILD_TYPE})         # 当前构建的类型，例如 Debug、Release
message(${CMAKE_CXX_STANDARD})       # C++ 标准
message(${CMAKE_C_STANDARD})         # C 标准
message(${PROJECT_NAME})             # 当前项目名
message(${LIBRARY_OUTPUT_PATH})      # 生成的库的输出路径
message(${EXECUTABLE_OUTPUT_PATH})   # 生成的目标的输出路径
# set 内置变量时不需要 ${}
set(PROJECT_NAME hello-cmake)

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
# STRLESS
# ...

# 版本比较
# VERSION_LESS
# ...

# 文件属性
# IS_DIRECTORY
if(IS_DIRECTORY "./")
    message(yes)
endif()
# IS_SYMLINK

# 文件时间戳比较
# IS_NEWER_THAN

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

if(APPLE)
  message("current OS is Apple")
elseif(UNIX)
  message("current OS is UNIX")
elseif(WIN32)
  message("current OS is Windows")
else()
  message("current OS is unknown")
endif()


# foreach

## foreach([loop_var] RANGE [max])
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

### Project Configure

#### Method 1

```sh
# 项目树
- test1
    - include
        * test.h
    - src
        * test.cpp
    * CMakeLists.txt
    * main.cpp
```

```cmake
# ./CMakeLists.txt
cmake_minimum_required(VERSION 3.20.0)
project(test1 CXX)
add_executable(app main.cpp src/test.cpp)
```

```cpp
// ./include/test.h
#ifndef _TEST_H_
#define _TEST_H_

void test();

#endif // _TEST_H_

// ./src/test.cpp
#include "../include/test.h"
#include <iostream>

void test() { puts("test"); }

// ./main.cpp
#include "include/test.h"

int main(int argc, char const *argv[]) {
    test();
    return 0;
}
```

#### Method 2

- include 方法可以引用子目录中的 cmake 配置文件，将配置加入 add_executable 中

```sh
# 项目树
- test2
    - include
        * test.h
    - src
        * test.cmake
        * test.cpp
    * CMakeLists.txt
    * main.cpp
```

```cmake
# ./src/test.cmake
set(test_source src/test.cpp)

# ./CMakeLists.txt
cmake_minimum_required(VERSION 3.20.0)
project(timer CXX)
include(src/test.cmake)
add_executable(app main.cpp ${test_source})
```

```cpp
// ./include/test.h
#ifndef _TEST_H_
#define _TEST_H_

void test();

#endif // _TEST_H_

// ./src/test.cpp
#include "../include/test.h"
#include <iostream>

void test() { puts("test"); }

// ./main.cpp
#include "include/test.h"

int main(int argc, char const *argv[]) {
    test();
    return 0;
}
```

#### Method 3

CMakeLists 嵌套

```sh
# 项目树
- test3
    - include
        * test.h
    - src
        * CMakeLists.txt
        * test.cpp
    * CMakeLists.txt
    * main.cpp
```

```cmake
# ./src/CMakeLists.txt
add_library(testlib test.cpp)

# ./CMakeLists.txt
cmake_minimum_required(VERSION 3.20.0)
project(test3 CXX)
add_subdirectory(src)
add_executable(app main.cpp)
target_link_libraries(app PUBLIC testlib)
target_include_directories(app PUBLIC include)
```

```cpp
// ./include/test.h
#ifndef _TEST_H_
#define _TEST_H_

void test();

#endif // _TEST_H_

// ./src/test.cpp
#include "../include/test.h"
#include <iostream>

void test() { puts("test"); }

// ./main.cpp
#include "test.h"

int main(int argc, char const *argv[]) {
    test();
    return 0;
}
```

#### Method 4

版本要求：3.12

- add_library OBJECT，Object Library 是一个特殊的库类型，将目标文件编译成一个库，但不会生成最终的链接文件，可以在 add_library 或 add_executable 中将 Object Library 作为源文件进行链接，从而生成最终的可执行文件或库文件

```sh
# 项目树
- test4
    - include
        * test1.h
        * test2.h
    - src
        * CMakeLists.txt
        * test1.cpp
        * test2.cpp
    * CMakeLists.txt
    * main.cpp
```

```cmake
# ./src/CMakeLists.txt
file(GLOB SRC *.cpp)
add_library(libtest OBJECT ${SRC})

# ./CMakeLists.txt
cmake_minimum_required(VERSION 3.20.0)
project(test4 CXX)
add_subdirectory(src)
add_executable(app main.cpp)
target_link_libraries(app PUBLIC libtest)
target_include_directories(app PUBLIC ${PROJECT_SOURCE_DIR}/include)
```

```cpp
// ./include/test1.h
#ifndef _TEST_H_
#define _TEST_H_

void test1();

#endif // _TEST1_H_

// ./include/test2.h
#ifndef _TEST2_H_
#define _TEST2_H_

void test2();

#endif // _TEST2_H_

// ./src/test1.cpp
#include <iostream>

void test1() { puts("test1"); }

// ./src/test2.cpp
#include <iostream>

void test2() { puts("test2"); }

// ./main.cpp
#include "test1.h"
#include "test2.h"

int main(int argc, char const *argv[]) {
    test1();
    test2();
    return 0;
}
```

### Static And Dynamic Libraries

Windows 静态库 libxxx.lib，动态库 libxxx.dll （需要全名）

Unix 静态库 libxxx.a，动态库 libxxx.so （只需要给出 xxx，默认带 lib 前缀）

静态库生成后可以修改名称，动态库生成后不能修改名称

```cmake
file() # 搜索源文件

# 生成静态库
add_library(test STATIC ${SRC}) # Unix -> libtest.a
## add_library(test STATIC ${SRC}) # Windows -> test.lib 

# 生成动态库
add_library(test SHARED ${SRC}) # Unix -> libtest.so
## add_library(test SHARED ${SRC}) # Windows -> test.dll

${LIBRARY_OUTPUT_PATH} # 库导出目录
```

```sh
# 项目树
- generate-libraries
    - include
        * test.h
    - src
        * test.cpp
    * CMakeLists.txt
```

#### Generate Static library

```cmake
# ./CMakeLists.txt
cmake_minimum_required(VERSION 3.20.0)
project(generate-libraries CXX)

file(GLOB SRC ${PROJECT_SOURCE_DIR}/src/*.cpp)
include_directories(${PROJECT_SOURCE_DIR}/include)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# generate static library
add_library(test STATIC ${SRC}) # Unix
## add_library(libtest STATIC ${SRC}) # Windows
```

#### Generate Dynamic library

```cmake
# ./CMakeLists.txt
cmake_minimum_required(VERSION 3.20.0)
project(generate-libraries CXX)

file(GLOB SRC ${PROJECT_SOURCE_DIR}/src/*.cpp)
include_directories(${PROJECT_SOURCE_DIR}/include)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# generate shared library
add_library(test SHARED ${SRC}) # Unix
## add_library(libtest SHARED ${SRC}) # Windows
```

#### Call Static Library

1. 引入头文件
2. 链接静态库
3. 生成可执行二进制文件

```sh
# 项目树
- call-lib
    - include
        * test.h
    - lib
        * libtest.a # Unix
        # libtest.lib # Windwos
    * CMakeLists.txt
    * main.cpp
```

```cmake
# ./CMakeLists.txt
cmake_minimum_required(VERSION 3.20.0)
project(call-lib CXX)

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)
link_libraries(test) # Unix
## link_libraries(libtest) # Windows
add_executable(app main.cpp)
```

```cpp
// ./include/test.h
#ifndef _TEST_H_
#define _TEST_H_

void test();

#endif // _TEST_H_

// ./main.cpp
#include "test.h"

int main(int argc, char const *argv[]) {
    test();
    return 0;
}
```

#### Call Dynamic Library

1. 引入头文件
2. 声明库目录
3. 生成可执行二进制文件
4. 链接动态库

```sh
# 项目树
- call-dll
    - include
        * test.h
    - dll
        * libtest.so # Unix
        # libtest.dll # Windows
    * CMakeLists.txt
    * main.cpp
```

```cmake
# ./CMakeLists.txt
cmake_minimum_required(VERSION 3.20.0)
project(call-so CXX)

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/so)
add_executable(app main.cpp)
target_link_libraries(app PUBLIC test) # Unix
## target_link_libraries(app PUBLIC libtest) # Windows

# Windows 上需要让动态库和可执行文件处于同一目录
```

```cpp
// ./include/test.h
#ifndef _TEST_H_
#define _TEST_H_

void test();

#endif // _TEST_H_

// ./main.cpp
#include "test.h"

int main(int argc, char const *argv[]) {
    test();
    return 0;
}
```

### Interaction

```sh
# 项目树
- interaction
    * CMakeLists.txt
    * config.h
    * main.cpp
```

```cmake
# ./CMakeLists.txt
cmake_minimum_required(VERSION 3.20.0)
project(interaction CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
configure_file(config.h.in config.h)
add_executable(app main.cpp)
target_include_directories(app PUBLIC ${PROJECT_BINARY_DIR})
```

```cpp
// ./config.h
#define CMAKE_CXX_STANDARD ${CMAKE_CXX_STANDARD}
#define PROJECT_SOURCE_DIR "${PROJECT_SOURCE_DIR}"
#define CMAKE_VERSION "${CMAKE_VERSION}"

// ./main.cpp
#include <iostream>
#include "config.h"

int main(int argc, char const *argv[]) {
    std::cout << CMAKE_CXX_STANDARD << std::endl;
    std::cout << PROJECT_SOURCE_DIR << std::endl;
    std::cout << CMAKE_VERSION << std::endl;
    return 0;
}
```

### Conditional Compilation

通过传入不同的参数编译不同的文件

1. 用 option 定义变量
2. 在子 CMakeList.txt 中根据变量 ON 或 OFF 修改源文件及 target_compile_definitions
3. 修改源文件根据变量选择代码
4. 执行命令时 -D<变量>=ON/OFF 进行条件编译

```sh
# 项目树
- conditional-compilation
    - include
        * test1.h
        * test2.h
    - src
        * CMakeLists.txt
        * test1.cpp
        * test2.cpp
    * CMakeLists.txt
    * main.cpp
```

```cmake
# ./src/CMakeLists.txt
option(USE_TEST1 "Use test1" ON) # 默认给定 ON

set(SRC test2.cpp)
if(USE_TEST1)
    set(SRC test1.cpp ${SRC})
endif()

add_library(libtest ${SRC})

if(USE_TEST1)
    target_compile_definitions(libtest PUBLIC "USE_TEST1") # 目标文件编译时添加 USE_TEST1 宏定义
endif()

# ./CMakeLists.txt
cmake_minimum_required(VERSION 3.20.0)
project(conditional-compilation CXX)

include_directories(${PROJECT_SOURCE_DIR}/include)
add_subdirectory(src)
add_executable(app main.cpp)
target_link_libraries(app PUBLIC libtest)
```

```cpp
// ./include/test1.h
#ifndef _TEST1_H_
#define _TEST1_H_

void test1();

#endif // _TEST1_H_

// ./include/test2.h
#ifndef _TEST2_H_
#define _TEST2_H_

void test2();

#endif // _TEST2_H_

// ./src/test1.cpp
#include "test1.h"
#include <iostream>

void test1() { puts("test1"); }

// ./src/test2.cpp
#include "test2.h"
#include <iostream>

void test2() { puts("test2"); }

// ./main.cpp
#ifdef USE_TEST1
#include "test1.h"
#endif
#include "test2.h"
#include <iostream>

int main(int argc, char const *argv[]) {
#ifdef USE_TEST1
    test1();
#endif
    test2();
    return 0;
}
```

```sh
# build result
$ cmake -B build -DUSE_TEST1=ON
// $ cmake -B build
...
$ cmake --build build
...
$ .\build\Debug\app.exe
// $ ./build/app
test1
test2


$ cmake -B build -DUSE_TEST1=OFF
...
$ cmake --build build
...
$ .\build\Debug\app.exe
// $ ./build/app
test2
```

### add_subdirectory

包含子目录的 `CMakeLists.txt` 文件，将这个文件的内容加入到当前 `CMakeLists.txt`

```cmake
add_subdirectory(
    ${PROJECT_SOURCE_DIR}/global
)
```



### configure_file

复制配置文件到可执行文件目录：

```cmake
configure_file(
    ${PROJECT_SOURCE_DIR}/config.ini
    ${PROJECT_BINARY_DIR}/config.ini
    COPYONLY
)
```

### find_libraries

查找指定路径下查找指定的动态库文件：

```cmake
find_libraries(
    redis_lib
    NAMES hiredis
    PATH /usr/local/lib
)
```

### find_package

```cmake
find_package(gRPC CONFIG REQUIRED)
```

### include_directories

包含项目包含的头文件：

```cmake
include_directories(
    ${PROJECT_SOURCE_DIR}
)
```

### include

包含 .cmake 所在的目录

```cmake

```

### link_directories

```cmake

```

### link_libraries

```cmake

```

### target_link_directories

```cmake

```

### target_link_libraries

静态库使用 target_link_libraries

```cmake
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/lib
)
```

### target_include_directories

项目包含目录

```cmake
target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)
```

### CMakeLists.txt 与 .cmake

每个 CMake 项目的根目录都必须包含一个 `CMakeLists.txt` 文件（名称固定），定义了 CMake 版本，项目的名称、版本、要构建的目标（可执行文件、库等）、依赖项以及其他构建选项。

`.cmake` 通常用于定义可重用的函数、宏和变量，定义的内容可以在 `CMakeLists.txt` 中使用（需要包含 `.cmake`  目录）。

`.cmake` 也可以查找外部库、设置编译器选项或定义自定义构建规则。例如用于查找和配置外部库。
