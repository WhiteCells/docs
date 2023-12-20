### CMake 特点

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
CMAKE_MINIMUM_REQUIRED(VERSION 3.20) # 最低版本要求
PROJECT(project-name) # 项目名
ADD_EXECUTABLE(project-name main.cpp) # 由源文件生成一个可执行的程序
```

```sh
cmake -B build # 创建一个 build 目录并在此目录下生成构建文件
cmake --build build # 生成项目
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
```

```cmake
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

