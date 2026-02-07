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

