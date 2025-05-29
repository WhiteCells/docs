### Windows CMake

[CMake installation](https://cmake.org/download/)

默认生成 MSVC 构建文件

### Linux CMake

包管理器安装：

```sh
# 
sudo apt install cmake
```

源码安装：

```sh
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

