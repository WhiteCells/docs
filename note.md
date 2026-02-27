```sh
git clone https://huggingface.co/jingyaogong/MiniMind2
paru -S git-lfs
git lfs install
git lfs pull
```

---

```sh
# 查看显卡占用
nvitop # 也可以查看A卡或I卡
nvidia-smi
```

---

google可以访问，但是插件和账号都无法正常访问，尝试切换 DNS

---

clangd 的索引依赖于 Ninja 生成的 compile_commands.json 文件

```sh
cmake -B build -G Ninja
```

使用 CMake 时需要使用如下设置以开启 compile_commands.json 导出：

```cmake
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
```

---

```sh
# conda 环境中配置 pip 全局源
pip config set global.index-url https://mirrors.aliyun.com/pypi/simple/
```

---

修改项目使用 clang 作为编译器（如果原先 build 非 clang，需要删除 build，重新构建）。

```sh
CC=clang CXX=clang++ cmake -B build
# or
cmake -B build \
  -DCMAKE_C_COMPILER=clang \
  -DCMAKE_CXX_COMPILER=clang++
```

使用 CMakeLists.txt 则需要写在 `project()` 之前，因为编译器在 `project()` 之前就已经确定（不推荐）：

```cmake
cmake_minimum_required(VERSION 3.16)
if (NOT CMAKE_CXX_COMPILER)
    find_program(CLANGXX clang++)
    if (CLANGXX)
        set(CMAKE_C_COMPILER clang)
        set(CMAKE_CXX_COMPILER clang++)
    endif()
endif()
project(VL)
set(CMAKE_CXX_STANDARD 17)
add_executable(${PROJECT_NAME} src/test.cpp)
```

正确使用 clang 的日志：

```sh
-- The C compiler identification is Clang 21.1.6
-- The CXX compiler identification is Clang 21.1.6
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/clang - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/clang++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
```

---

```sh
docker run --name fs1 \
  -p 5060:5060/tcp -p 5060:5060/udp \
  -p 5080:5080/tcp -p 5080:5080/udp \
  -p 8021:8021/tcp \
  -p 5066:5066/tcp \
  -p 7443:7443/tcp \
  -p 8081:8081/tcp -p 8082:8082/tcp \
  -p 16384-32768:16384-32768/udp \
  fs

docker run --name fs1 \
  -p 8081:8081/tcp -p 8082:8082/tcp \
  -p 16384-32768:16384-32768/udp \
  fs
  
docker run --name fs1 \
  -p 16384-32768:16384-32768/udp \
  fs

docker run --name fs1 \
  --userland-proxy=false \
  -p 5060:5060/tcp -p 5060:5060/udp \
  -p 5080:5080/tcp -p 5080:5080/udp \
  -p 8021:8021/tcp \
  -p 5066:5066/tcp \
  -p 7443:7443/tcp \
  -p 8081:8081/tcp -p 8082:8082/tcp \
  fs
  

docker run --name fs1 fs

docker run --name fs1 --network host fs


docker run \
  --name fs1 \
  --network host \
  -v $(pwd)/conf:/usr/local/freeswitch/conf \
  -v $(pwd)/recordings:/usr/local/freeswitch/recordings \
  -v $(pwd)/log:/usr/local/freeswitch/log \
  fs

docker run \
  --name fs1 \
  --network host \
  -v ./conf:/etc/freeswitch \
  -v ./recordings:/var/lib/freeswitch/recordings \
  -v ./log:/var/log/freeswitch \
  fs

docker run \
  --name fs1 \
  --network host \
  -u $(id -u):$(id -g) \
  -v $(pwd)/conf:/usr/local/freeswitch/conf \
  -v $(pwd)/recordings:/usr/local/freeswitch/recordings \
  -v $(pwd)/log:/usr/local/freeswitch/log \
  fs

docker run -d \
  --name fs1 \
  -e TZ=Asia/Shanghai \
  --network host \
  fs

docker run -d \
  --name fs2 \
  -e TZ=Asia/Shanghai \
  --network host \
  fs
```

---

需要 push 的仓库，在 clone 仓库时不建议使用 --depth 1

