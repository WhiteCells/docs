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

---

```sh
tree -L 1 --dirsfirst
```

```sh
vim /etc/fail2ban/jail.d/sshd.local
```

```sh
[sshd]
enabled = true
port    = 7890
# 如果你改了 SSH 端口（比如 22022），这里要写成 port = 22022

# 日志检测模式：normal, ddos, extra 或 aggressive
# aggressive 会监测非法用户尝试（像你日志里的 user01/user02）
mode    = aggressive

# 强制指定后端。如果 systemd 不行，我们换成文件读取
backend = auto
# 指定日志路径（Debian/Ubuntu 通常是这个）
logpath = /var/log/auth.log

# 封禁策略
findtime  = 10m
maxretry  = 3
bantime   = 24h

# 封禁动作：如果你用的是 ufw，改用 ufw；如果用 nftables，确保环境已装
banaction = iptables-multiport
```

```sh
fail2ban-client status sshd

# 实时看 fail2ban 自己的日志
tail -f /var/log/fail2ban.log

# 看 ssh 登录失败日志
tail -f /var/log/auth.log

# 手动 ban IP
fail2ban-client set sshd banip 1.2.3.4

# 解封 IP
fail2ban-client set sshd unbanip 1.2.3.4

# 重新加载 fail2ban-client 配置
fail2ban-client reload
```

时区

```sh
timedatectl
```

```sh
date
ls -l /etc/localtime
cat /etc/timezone   # 部分发行版有这个文件
timedatectl list-timezones
timedatectl list-timezones | grep Shanghai
timedatectl set-timezone Asia/Shanghai
```

