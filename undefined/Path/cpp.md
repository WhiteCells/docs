### Linux

```sh
# 添加一个新的 PPA（Personal Package Archive）源，来获取最新版本的 g++
sudo add-apt-repository ppa:ubuntu-toolchain-r/test

# 更新软件包列表
sudo apt update

# 安装 g++-10 这个版本的 g++ 编译器
sudo apt install g++-10

# 查看是否安装成功
g++-10 --version

# 使用新版本
g++-10 main.cpp -o main

# 创建一个符号链接，将 g++-10 命令替换为 g++ 命令
sudo ln -s /usr/bin/g++-10 /usr/bin/g++

# sudo ln -s /usr/bin/gcc-10 /usr/bin/gcc

sudo apt install gdb
```

如果出现 `ln: failed to create symbolic link '/usr/bin/g++': File exists` 错误，表示 `/usr/bin/g++` 已经存在了。

这可能是因为已经创建过了一个叫做 `/usr/bin/g++` 的符号链接

```sh
# 检查 /usr/bin/g++ 文件的类型
file /usr/bin/g++
# /usr/bin/g++: symbolic link 表示符号链接存在

# 删除符号链接
sudo rm /usr/bin/g++

# 创建符号链接，/usr/bin/g++ 指向 /usr/bin/g++-10
sudo ln -s /usr/bin/g++-10 /usr/bin/g++

# 检查符号链接是否创建成功
ls -l /usr/bin/g++
# /usr/bin/g++ -> /usr/bin/g++-10 表示符号链接创建成功

# 使用新版本
g++ main.cpp -o main
```

> ps：
>
> 1. vscode 运行 linux 中 IntelliSense 使用 gnu（避免 linux 中的宏提示不存在）
>
> 2. 移除 PPA 源，不移除无法安装低版本 GCC
>
>    ```sh
>    sudo add-apt-repository --remove ppa:ubuntu-toolchain-r/test
>    # 安装低版本 GCC 时出错
>    # The following packages have unmet dependencies
>    sudo apt-get install aptitude
>    sudo aptitude install g++
>    # 选择 no 后面都是 yes
>    ```

### Windows

[sourceforge](https://sourceforge.net) 上安装的版本为旧版本

[niXman/mingw-builds-binaries/releases ](https://github.com/niXman/mingw-builds-binaries/releases) github 上下载新版本

- 32位的操作系统，选择 i686，64位的操作系统，选择 x86_64；
- 13.1.0 是 GCC 的版本号；
- win32 是开发 windows 系统程序的协议，posix 是其他系统的协议（例如Linux、Unix、Mac OS）；
- 异常处理模型 seh（新的，仅支持64位系统），sjlj（稳定的，64位和32位都支持）， dwarf（优于sjlj的，仅支持32位系统）；
- msvcrt、ucrt 运行时库类型，
- MSVCRT（Microsoft Visual C Runtime）是 Microsoft Visual C++ 早期版本使用的运行时库，用于支持 C 程序的运行。它提供了一些常用的 C 函数，如 printf、scanf、malloc、free等。MSVCRT 只能在 32 位 Windows 系统上运行，对于 64 位系统和 Windows Store 应用程序不支持。UCRT（Universal C Runtime）是在 Windows 10 中引入的新的 C 运行时库，用于支持 C 程序的运行和开发。UCRT 提供了一些新的 C 函数，同时还支持 Unicode 字符集和安全函数，如 strcpy_s、strcat_s、_itoa_s 等。UCRT 同时支持 32 位和 64 位系统，并且可以与 Windows Store 应用程序一起使用；
- rev1 构建版本；

配置环境变量，bin 目录



### 相关链接

- https://www.mingw-w64.org/
- https://sourceforge.net
- https://github.com/niXman/mingw-builds-binaries/releases
