https://opencv.org/releases/

https://github.com/opencv/opencv

### Windows 配置 OpenCV 环境

使用 MinGW

```cmd
# 配置 CMake
cmake -G "MinGW Makefiles" \
-D CMAKE_BUILD_TYPE=Release \
-D CMAKE_INSTALL_PREFIX=<install_path> \
-D CMAKE_C_COMPILER=gcc.exe \
-D CMAKE_CXX_COMPILER=g++.exe \
-D BUILD_TESTS=OFF \
-D BUILD_PERF_TESTS=OFF \
../<opencv_source>

# 编译（CMD）
mingw32-make -j%NUMBER_OF_PROCESSORS%
# 编译（PowerShell）
mingw32-make -j$env:NUMBER_OF_PROCESSORS

# 安装
mingw32-make install
```

`D:\dev\env\opencv2\x64\mingw\bin` 添加到 `PATH`



#### CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.20)

project(opencv_test VERSION 1.0 LANGUAGES CXX)

set(OpenCV_DIR "D:\\dev\\env\\opencv\\x64\\mingw\\lib")

find_package(OpenCV REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})

target_include_directories(${PROJECT_NAME} PRIVATE ${OpenCV_INCLUDE_DIRS})
```

如果不想设置 `OpenCV_DIR` 可以添加 `OpenCV_DIR` 的环境变量



### Linux 配置 OpenCV 环境

```sh
# 4.10
wget https://github.com/opencv/opencv/archive/refs/tags/4.10.0.tar.gz \
-O opencv-4.10.0.tar.gz

tar -zxvf opencv-4.10.0.tar.gz
mv opencv-4.10.0 opencv

mkdir opencv_build
cd opencv_build
cmake -D CMAKE_BUILD_TYPE=Release \
-D CMAKE_INSTALL_PREFIX=/usr/local/opencv \
-D BUILD_TESTS=OFF \
-D BUILD_PERF_TESTS=OFF \
../opencv-4.10.0/

make -j

sudo make install
```

