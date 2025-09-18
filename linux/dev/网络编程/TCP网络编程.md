### 套接字地址结构

#### 套接字数据结构

```c
#include <sys/socket.h>

// 通用套接字地址类型的定义
struct sockaddr {
    sa_family_t     sa_family;      /* Address family */
    char            sa_data[];      /* Socket address */
};
```

通用套接字地址类型可以在不同协议族之间进行强制转换。

在网络编程中几乎所有的**套接字函数**都用 `sockaddr` 为参数。

但是使用 `struct sockaddr` 不方便进行设置，一般采用结构 `struct sockaddr_in` 进行设置，定义如下：

```c
#include <sys/socket.h>

struct sockaddr_in {
    sa_family_t     sin_family;     /* AF_INET */
    in_port_t       sin_port;       /* Port number */
    struct in_addr  sin_addr;       /* IPv4 address */
};

typedef uint32_t in_addr_t;
typedef uint16_t in_port_t;
```

IP 地址结构体 `struct in_addr` 定义如下：

```c
struct in_addr {
    in_addr_t s_addr;  /* 32 位 IP 地址，网络字节序 */
};
```

#### 结构体 sockaddr 和 sockaddr_in 的关系

`struct sockaddr` 和 `struct sockaddr_in` 是一个同样大小的结构，所以进行地址结构体设置时，通常的方法是使用 `struct sockaddr_in` 类型，然后强制转换为 `struct sockaddr` 类型。由于大小完全一致，所以转换不会有什么副作用。

#### 用户层和内核层交互过程

##### 向内核传入数据的交互过程

向内核传入数据的函数有 `send()`、`bind()` 等，从内核得到数据的函数有 `accept`、`recv()` 等。

调用 `bind()` 函数时，地址结构通过内存复制的方式将其中的内容复制到内核，地址结构长度的长度通过传值的方式传入内核，内核按照用户传入的地址结构长度来复制套接字地址结构的内容。

##### 内核传出数据的交互过程

通过地址结构的长度和套接字地址结构指针来进行地址结构参数的传出操作。通常是两个参数完成传出操作的功能，一个表示地址结构长度的参数，一个表示套接字地址结构地址的指针。

### TCP 网络编程流程

TCP 网络编程有两种模式，一个是服务器模式，另一个是客户端模式。服务器模式创建一个服务程序，等待客户端用户的连接，根据用户的请求进行处理。客户端模式根据目的服务器的地址和端口进行连接，向服务器发送请求并对服务器的响应进行数据处理。

#### 服务器端的设计

主要流程：

- **初始化套接字**：使用 `socket()` 函数，根据用户对套接字的需求来确定套接字的选项，系统根据用户需求生产一个套接字文件描述符供用户使用。
- **绑定套接字与端口**：使用 `bind()` 函数，将套接字与一个地址结构进行绑定，绑定之后，在进行网络程序设计时，套接字代表的 IP 地址和端口及协议类型等参数按照绑定值进行操作。
- **设置服务器的侦听连接**：使用 `listen()` 函数，由于一个服务器需要满足多个客户端的连接请求，而服务器在某个时间仅能处理有限个客户端连接请求，所以服务器需要设置服务端排队队列的长度，服务器监听连接会设置这个参数，限制客户端中等待服务器处理连接请求的队列长度。
- **接受客户端连接**：使用 `accept()` 函数，在客户端发送请求后，服务器需要接受客户端的连接，然后才能进行其他的处理。
- **读写数据**：使用 `read()`、`write()` 函数，从套接字文件描述符中读取数据或者发送数据。
- **处理数据**：接受数据后服务器按照定义的规则对数据进行处理，并将结果发送客户端。
- **关闭处理完毕的套接字**：使用 `close()` 函数，当服务器处理完数据，要结束与客户端的通信过程时，需要关闭套接字连接。

#### 客户端的设计

主要流程：

- **初始化套接字**：使用 `socket()` 函数，
- **连接服务器**：使用 `connect()` 函数，
- **读写数据**：使用 `read()`、`write()` 函数，
- **处理数据**：接受数据后客户端按照定义的规则对数据进行处理，并将结果发送客户端。
- **关闭套接字**：

#### 客户端与服务器端的交互过程



### 创建网络插口函数 socket()

- `#include <sys/socket.h>`
- `int socket(int domain, int type, int protocol);`
  - **parameter**
    - **domain**：协议族
    - **type**：协议类型
    - **protocol**：协议编号
  - **return**：成功返回套接字的文件描述符；失败返回 -1，并设置 errno

#### domain 参数

`domain` 用于设置网络通信的域，`socket()` 根据该参数选择通信协议族，通信协议族在文件 `sys/socket.h` 中定义。

`domain` 用于设置网络通信的域，其值及含义：

| 名称                  | 含义                       |
| --------------------- | -------------------------- |
| `PF_UNIX`，`PF_LOCAL` | 本地通信                   |
| `PF_INET`             | IPv4 Internet 协议         |
| `PF_INET6`            | PIv6 Internet 协议         |
| `PF_IPX`              | IPX - Novell 协议          |
| `PF_NETLINK`          | 内核用户界面设备           |
| `PF_X25`              | ITU-T X.25 / ISO-8208 协议 |
| `PF_AX25`             | Amateur radio AX.25 协议   |
| `PF_ATMPVC`           | 原始 ATM PVC 访问          |
| `PF_APPLETALK`        | Appletalk                  |
| `PF_PACKET`           | 底层包访问                 |

> 有的代码使用 `AF_INET` 这个值，在头文件中 `AF_INET` 和 `PF_INET` 的值是一致的

#### type 参数

`type` 用于设置套接字通信的类型，其值及含义：

| 名称             | 含义                                                         |
| ---------------- | ------------------------------------------------------------ |
| `SOCK_STREAM`    | TCP 连接，提供序列化的、可靠的、双向连接的字节流。支持带外数据传输 |
| `SOCK_DGRAM`     | 支持 UDP 连接                                                |
| `SOCK_SEQPACKET` | 序列化包，提供一个序列化的、可靠的、双向的基于连接的数据传输通道，数据长度定长，每次调用读系统调用时，需要将全部数据读出 |
| `SOCK_RAW`       | RAW 类型，提供原始网络协议访问                               |
| `SOCK_RDM`       | 提供可靠的数据报文，不过可能数据会乱序                       |
| `SOCK_PACKET`    | 专用类型，不能在通用程序中使用                               |

并不是所有协议族都实现了这些协议类型。

#### protocol 参数

`protocol` 用于指定某个协议的特定类型，即 `type` 类型中的某个类型，通常某个协议中只有一种特定类型，此时 `protocol` 仅能设置为 0，但是有些协议有多种特定的类型，就需要设置这个参数来选择特定的类型。

- `SOCK_STREAM` 的套接字表示一个双向的字节流，与管道类似，流式的套接字在进行数据收发之前必须已经连接，连接使用 `connect()` 函数进行，一旦连接，可以使用 `read()` 或 `write()` 函数进行数据的传输，流式通信方式保证数据不会丢失或者重复接收，当数据在一段时间内仍然没有接受完毕，可以认为该连接超时
- `SOCK_DGRAM` 和 `SOCK_RAW` 这两种套接字可以使用 `sendto()` 函数来发送数据，使用 `recvfrom()` 函数接收数据，`recvfrom()` 接受来自指定 IP 地址的发送方的数据
- `SOCK_PACKET` 是一个专用的数据包，直接从设备驱动接受数据

#### socket() 的 errno 值及含义

`socket()` 的 errno 的值及含义：

| 值                 | 含义                                            |
| ------------------ | ----------------------------------------------- |
| `EACCES`           | 没有权限建立指定 `domain` 的 `type` 的 `socket` |
| `EAFNOSUPPORT`     | 不支持所给的地址类型                            |
| `EINVAL`           | 不支持此协议或者协议不可用                      |
| `EMFILE`           | 进程文件表溢出                                  |
| `ENFILE`           | 已经达到系统允许打开的文件数量                  |
| `ENOBUFS`/`ENOMEM` | 内存不足                                        |
| `EPROTONOSUPPORT`  | 指定的协议 `type` 在 `domain` 中不存在          |



### 绑定一个地址端口对 bind()

- `#include <sys/socket.h>`
- `int bind(int socket, const struct sockaddr *address, socklen_t address_len);`
- **parameter**
  - **socket**：`socket` 文件描述符
  - **address**：指向结构为 `sockaddr` 参数的指针
  - **address_len**：`struct sockaddr` 的长度
- **return**：绑定成功返回 0；失败返回 -1，并设置 errno

将长度为 `address_len` 的 `address` 与 `socket` 绑定到某个端口上，如果使用 `connect()` 函数则没有绑定的必要。

#### socket 参数

由 `socket()` 函数创建的文件描述符。

#### address 参数

指向一个结构为 `sockaddr` 的指针，`sockaddr` 中包含地址、端口和 IP 地址的信息，在绑定时，需要先将地址结构中的 IP 地址、端口、类型等结构中的域进行设置后才能进行绑定。

#### address_len 参数

可以设置为 `sizeof(struct sockaddr)`

#### bind() 的 errno 值及含义

| 值              | 含义                                            | 备注                 |
| --------------- | ----------------------------------------------- | -------------------- |
| `EADDRINUSE`    | 地址已被使用                                    |                      |
| `EBADF`         | `socket` 文件描述符不合法                       |                      |
| `EINVAL`        | `socket` 已经绑定到其他地址                     |                      |
| `ENOTSOCK`      | `socket` 是一个文件描述符，不是 `socket` 描述符 |                      |
| `EACCES`        | 地址被保护，用户权限不足                        |                      |
| `EADDRNOTAVAIL` | 接口不存在或者绑定地址不是本地                  | UNIX 协议族，AF_UNIX |
| `EFAULT`        | `address` 指针超出用户空间                      | UNIX 协议族，AF_UNIX |
| `EINVAL`        | 地址长度错误，或者 `socket` 不是 `AF_UNIX` 族   | UNIX 协议族，AF_UNIX |
| `ELOOP`         | 解析 `address` 是符号链接过多                   | UNIX 协议族，AF_UNIX |
| `ENAMETOOLONG`  | `address` 过长                                  | UNIX 协议族，AF_UNIX |
| `ENOENT`        | 文件不存在                                      | UNIX 协议族，AF_UNIX |
| `ENOMEM`        | 内存内核不足                                    | UNIX 协议族，AF_UNIX |
| `ENOTDIR`       | 不是目录                                        | UNIX 协议族，AF_UNIX |
| `EROFS`         | socket 节点应该在只读文件系统上                 | UNIX 协议族，AF_UNIX |

#### bind() 函数的例子

```c
#include <sys/socket.h>  /* for socket() */
#include <netinet/in.h>  /* for struct sockaddr_in */
#include <arpa/inet.h>   /* for inet_addr() */
#include <unistd.h>      /* for close() */
#include <stdio.h>       /* for perror() */
#include <string.h>      /* for memset() */

int main(int argc, char *argv[]) {
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1) {
        perror("sfd socket");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_family = AF_INET;
    memset(&addr.sin_zero, 0, sizeof(addr.sin_zero));

    if (bind(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr)) == -1) {
        perror("sfd bind");
        return 1;
    }

    close(sfd);

    return 0;
}
```



### 监听本地端口 listen()

- `#include <sys/socket.h>`
- `int listen(int socket, int backlog);`
  - **parameter**
    - **socket**：`socket` 文件描述符
    - **backlog**：等待队列的长度
  - **return**：监听成功返回 0；失败返回 -1，并设置 errno

在接受一个连接之前，需要使用 `listen()` 函数来侦听端口，`listen()` 函数仅对类型为 `SOCK_STREAM` 或者 `SOCK_SEQPACKET` 的协议有效。

函数 `listen()` 用于初始化服务器可连接队列，服务器处理客户端连接请求的时是顺序处理的，同一时间仅能处理一个客户端连接，当多个客户端连接请求同时到来的时，服务器并不是同时处理，而是将不能处理的客户端连接放到等待队列中，这个队列长度又 `listen()` 函数定义。

#### socket 参数

`socket` 文件描述符

#### backlog 参数

参数 `backlog` 表示在 `accept()` 函数处理之前在等待队列中的客户端的长度，如果超出该长度，客户端会返回一个 `ECONNREFUSED` 错误

#### listen 的 errno 值及含义

| 值           | 含义                          |
| ------------ | ----------------------------- |
| `EADDRINUSE` | 端口被另一个 `socket` 占用    |
| `EBADF`      | `socket` 不合法               |
| `ENOTSOCK`   | `socket` 不是套接字文件描述符 |
| `EOPNOTSUPP` | `socket` 不支持 `listen()`    |

#### listen() 函数的例子

```c
#include <sys/socket.h>  /* for listen() */
#include <netinet/in.h>  /* for struct sockaddr_in */
#include <arpa/inet.h>   /* for inet_addr() */
#include <unistd.h>      /* for close() */
#include <string.h>      /* for bzero() */
#include <stdio.h>       /* for perror() */

int main(int argc, char *argv[]) {
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1) {
        perror("sfd socket");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(10101);
    bzero(&addr.sin_zero, sizeof(addr.sin_zero));

    if (bind(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr)) == -1) {
        perror("sfd bind");
        return 1;
    }

    if (listen(sfd, 5)) {
        perror("listen sfd");
        return 1;
    }

    close(sfd);

    return 0;
}
```

### 接受一个网络请求 accept()

- `#include <sys/socket.h>`
- `int accept(int socket, struct sockaddr *restrict address, socklen_t *restrict  address_len);`
  - **parameter**
    - **socket**：套接字文件描述符
    - **address**：传出参数，
    - **address_len**：指向 `address` 长度的指针
  - **return**：成功返回新连接的客户端套接字文件描述符；失败返回 -1，并设置 errno

当一个客户端连接请求达到服务器监听等待队列上限时，此时客户端的连接会在队列中等待，直到使用服务器处理接受请求。

函数 `accept()` 成功执行后，会返回一个新的套接口文件描述符来表示客户端的连接，客户端连接的信息可以通过这个新描述符来获得。因此服务器成功处理客户端的请求连接后，会有两个文件描述符，旧的文件描述符表示正在监听的 socket，新的文件描述符表示客户端的连接，函数 `send()` 和 `recv()` 通过新的文件描述符进行数据收发。

#### socket 参数



#### address 参数



#### address_len 参数



#### accept() 的 errno 值及含义

| 值                     | 含义                                          |
| ---------------------- | --------------------------------------------- |
| `EAGAIN`/`EWOULDBLOCK` | socket 使用了非阻塞模式，当前没有可接受的连接 |
| `EBADF`                | 描述符非法                                    |
| `ECONNABORRED`         | 连接取消                                      |
|                        |                                               |
|                        |                                               |
|                        |                                               |
|                        |                                               |
|                        |                                               |
|                        |                                               |
|                        |                                               |
|                        |                                               |
|                        |                                               |
|                        |                                               |

#### accept() 函数的例子

```c
#include <sys/socket.h>  /* for listen() */
#include <netinet/in.h>  /* for struct sockaddr_in */
#include <arpa/inet.h>   /* for inet_addr() */
#include <unistd.h>      /* for close() */
#include <string.h>      /* for bzero() */
#include <stdio.h>       /* for perror() */

int main(int argc, char *argv[]) {
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1) {
        perror("fsd socket");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(10101);
    bzero(addr.sin_zero, sizeof(addr.sin_zero));

    if (bind(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr)) == -1) {
        perror("bind fsd");
        return 1;
    }

    if (listen(sfd, 1) == -1) {
        perror("listen fsd");
        return 1;
    }

    struct sockaddr_in client_addr;
    socklen_t len = sizeof(struct sockaddr_in);
    int client_sfd = accept(sfd, (struct sockaddr *)&client_addr, &len);
    if (client_sfd == -1) {
        perror("fsd accept");
        return 1;
    }

    close(client_sfd);

    return 0;
}
```

### 连接目标网络服务器 connect()

- `#include <sys/socket.h>`
- `int connect(int socket, const struct sockaddr *address, socklen_t address_len);`
  - **parameter**
    - **socket**：
    - **address**：
    - **address_len**：
  - **return**：连接成功返回 0；失败返回 -1，并设置 errno

客户端在建立套接字之后，不想要进行地址绑定，就可以直接连接服务器，连接服务器函数 `connect()` 需要指明服务器参数。

#### socket 参数



#### address 参数



#### address_len 参数



#### connect() 的 errno 及含义

| 值   | 含义 |
| ---- | ---- |
|      |      |
|      |      |
|      |      |
|      |      |
|      |      |
|      |      |
|      |      |
|      |      |
|      |      |
|      |      |
|      |      |
|      |      |
|      |      |
|      |      |
|      |      |

#### connect() 函数的例子





### 写入数据函数 write()





### 读取数据函数 read()





### 关闭套接字函数 close()



