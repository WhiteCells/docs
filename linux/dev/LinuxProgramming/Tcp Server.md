### 套接字

套接字（socket） API 是 Linux 提供的一组网络编程接口，通过套接字 API 可以在网络传输层之上进行网络编程，也可以跨越传输层，直接对网络层进行开发。

套接字是 TCP/IP 网络编程中的基本操作单元，可以看作不同主机的进程之间的相互通信的端点。套接字是应用层与 TCP/IP 协议族通信的中间软件抽象层，将复杂的 TCP/IP 协议族隐藏于套接字接口。

socket 源于 UNIX，在 Windows 和 Linux 平台都对套接字实现的了编程接口，Windows 下 socket 实现叫 Windows socket，Linux 下有两套实现：一套是伯克利套接字（Berkely sockets），源于 Berkely UNIX，接口简单，应用广泛，是 Linux 网络编程标准；另一套是传输层接口（Transport Layer Interface，TLI），是 System V 系统上的网络编程 API，该接口更多的在 UNIX 上使用。

### 网络程序的架构

网路程序通常有两种架构：B/S（Browser/Server）和 C/S（Client/Server）。

### IP 地址格式的转换

将点分十进制形式的字符串 IP 地址（192.168.0.1）与二进制 IP 地址（11000000101010000000000000000001）相互转换。

使用函数 `inet_aton`、`inet_addr` 和 `inet_ntoa` 实现转换，这三个函数只能处理 IPv4 地址。

`inet_ntoa` 函数用于将 `in_addr` 转换到点分十进制的字符串 IP 地址。

```c

```



`inet_aton` 函数已被弃用，使用 `inet_pton` 函数代替。

```c

```





