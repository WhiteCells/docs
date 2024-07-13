### gRPC 简介

[github grpc](https://github.com/grpc/grpc)

[gRPC C++ quickstart](https://grpc.io/docs/languages/cpp/quickstart/)

gRPC 是 Google 开发的高性能、开源的远程调用（RPC）框架，使客户端方便客户端调用远程服务，并提供多种语言支持。

gRPC 使用 Protocol Buffers 作为数据格式，可以在不同的平台上进行应用程序之间的通信，采用 HTTP/2 的协议，提供高效、可拓展的远程调用功能，并带有负载均衡、认证、监控等功能。方便用户管理和维护分布式系统。

### Linux gRPC

#### 克隆 gRPC 仓库

```sh
git clone --recurse-submodules -b v1.65.0 --depth 1 --shallow-submodules https://github.com/grpc/grpc
```

```sh
git clone \
# 递归克隆子模块
--recurse-submodules \
# 分支
-b v1.65.0 \
# 克隆深度，浅层克隆子模块，克隆最近的提交历史
--depth 1 --shallow-submodules \
https://github.com/grpc/grpc
```

#### 构建和安装  gRPC 和 Protocol Buffers

```sh
export INSTALL_DIR=$HOME/.local

mkdir -p $INSTALL_DIR
export PATH="$INSTALL_DIR/bin:$PATH"

git clone --recurse-submodules -b v1.37.1 https://github.com/grpc/grpc

cd grpc

mkdir -p cmake/build
pushd cmake/build

cmake -DgRPC_INSTALL=ON -DgRPC_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR ../..
make -j
make install
popd

mkdir -p third_party/abseil-cpp/cmake/build
pushd third_party/abseil-cpp/cmake/build

cmake -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR -DCMAKE_POSITION_INDEPENDENT_CODE=TRUE ../..
make -j
make install
popd
```

```sh
# 设置环境变量，用作安装 gRPC 的目录
export gRPC_INSTALL_DIR=/usr/local

# 进入源码根目录
cd grpc

# 创建并进入构建目录
mkdir -p cmake/build
pushd cmake/build

# 启用安装 gRPC 目标
# 禁用构建测试
# 设置安装路径
# 指定 CMakeLists.txt 所在目录
cmake -DgRPC_INSTALL=ON \
      -DgRPC_BUILD_TESTS=OFF \
      -DCMAKE_INSTALL_PREFIX=$gRPC_INSTALL_DIR \
      ../..

# 使用 4 个并行线程运行 make 编译项目
make -j 4

# 安装编译的 gRPC 库和相关文件到 $gRPC_INSTALL_DIR
sudo make install

# 回到之前的目录
popd
```

#### 使用 Protobuf

```sh
protoc -I=. --cpp_out=. --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` message.proto
```

```sh
# Protocol Buffers 编译器
protoc \

# .proto 文件的目录
-I=. \

# 指定生成的 C++ 代码文件（.pb.cc .pb.h）的输出目录
--cpp_out=. \

# 指定生成的 gRPC 代码文件（.grpc.pb.cc .grpc.pb.h）的输出目录
--grpc_out=. \

# 指定使用的 gRPC 插件
--plugin=protoc-gen-grpc=`which grpc_cpp_plugin` \

# 指定编译的 .proto 文件
message.proto
```

#### CMakeLists

```cmake
find_package(ProtoBuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

target_link_libraries(app PRIVATE
    protobuf::libprotobuf
    gRPC::grpc++_reflection
    gRPC::grpc++
)
```

