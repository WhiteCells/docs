### 创建 socket

```cpp
#include <sys/socket.h>

int socket(int domain, int type, int protocol);
    argument:
        - domain: 通讯的协议家族
            - PF_INET: IPv4 互联网协议族
            - PF_INET6: IPv6 互联网协议族
            - PF_LOCAL: 本地通信协议族
            - PF_PACKET: 内核底层协议族
            - PF_IPX: IPX Novell 协议族
        - type: 数据传输的类型
            - SOCK_STREAM: 面向连接的 socket
                           1. 数据不会丢失
                           2. 数据顺序不会错乱
                           3. 双向通道
            - SOCK_DGRAM: 无连接的 socket
                          1. 数据可能丢失
                          2. 数据的顺序可能错乱
                          3. 传输效率更高
        - protocol: 使用的协议
                    数据传输方式为 SOCK_STREAM 的协议只有 IPPROTO_TCP
                    数据传输方式为 SOCK_DGRAM 的协议只有 IPPROTO_UDP
                    本参数也可以填 0
```

