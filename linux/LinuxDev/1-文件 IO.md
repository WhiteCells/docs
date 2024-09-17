### 1.文件描述符

在内核中，所有打开的文件都过文件描述符引用。文件描述符是一个非负数，范围在 `0` 至 `OPEN_MAX - 1`，当进程创建时默认为它打开 3 个文件描述符，它们始终链接终端：

- `STDIN_FILENO`：标准输入 （0）
- `STDOUT_FILENO`：标准输出（1）
- `STDERR_FILENO`：标准错误输出（2）

使用 `STDIN_FILENO`、`STDOUT_FILENO`、`STDERR_FILENO` 代替 0、1、2 从而提高可读性，可移植性及维护性，这 3 个宏位于 `<unistd.h>` 中

#### 1.1 复制文件描述符

```c
#include <stdio.h>

// 复制文件描述符
int dup(int oldfd);
    argument:
        - oldfd: 需要复制的文件描述符
    return: 
        - 成功返回新的文件描述符，
          新的文件描述符是当前可用的最小的文件描述符
        - 失败返回 -1

// dup2 系统调用执行与 dup 相同的任务，但它不使用编号最低的未使用文件描述符，
// 而是使用 newfd 中指定的文件描述符编号
// 如果文件描述符 newfd 以前是打开的，那么它在被重用之前会被关闭，是一个原子操作
int dup2(int oldfd, int newfd);
    argument:
        - oldfd: 需要复制 oldfd 文件描述符
        - newfd: 复制到 newfd 文件描述符

    return:
        - 成功返回 newfd
        - 失败返回 -1，并设置 errno

    note:
        - 如果 oldfd 无效，复制失败，newfd 不会被关闭
        - 如果 oldfd 和 newfd 相等则什么都不会做，返回 newfd

// 这些函数返回的新文件描述符与参数 oldfd 共享一个文件表项
// （文件表项） 文件状态标志、当前文件偏移量、v 节点指针
```

### 2. 相关调用

#### 2.1 打开文件

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// 打开指定路径下文件或目录
int open(const char *pathname, int flags);
    argument:
        - pathname: 需要打开的文件的路径
        - flags:
            - 必须指定一个:
                - O_RDONLY: 只读
                - O_WRONLY: 只写
                - O_RDWR: 读写
                - O_EXEC: 只执行打开（某些系统可用）
                - O_SEARCH: 只搜索打开（应用于目录）（某些系统可用）
            - 使用按位或 | 的方式附加 0 个或多个，
                - O_APPEND: 文件以追加方式打开，在每次写入 write 之前文件偏移量 offset 位于文件末尾，是一个原子操作
                - O_ASYNC: 启用信号驱动 I/O
                - O_SYNC: 以同步写入方式打开文件，确保写入立即被写入磁盘。
                - O_DSYNC: 文件写入操作会保证数据的完整性
                - O_RSYNC: 使每一个 read 操作等待，直到所有对文件同一部分挂起的写操作完成
                - O_CREAT: 如果指定路径下文件不存在，将其创建为常规文件
                - O_DIRECT: 尽量减少此文件的 I/O 对缓存的影响
                - O_CLOEXEC: 在执行 exec 系统调用时关闭文件描述符
                - O_DIRECTORY: 打开目录，如果路径 pathname 不是目录，则 open 失败
                - O_EXCL: 与 O_CREAT 一起使用，如果文件已经存在，则 open 失败
                - O_NOCTTY: 如果文件是终端设备，不将其分配为控制终端
                - O_LARGEFILE: 处理大文件（这个标志可能已经不再是必需的）
                - O_NOFOLLOW: 直接操作符号链接而不是其指向的文件
                - O_TMPFILE: 在文件系统中创建一个不与目录关联的临时文件
                - O_TRUNC: 如果文件存在，将其截断为空文件
                - O_NONBLOCK: 以非阻塞模式打开文件

    return: 
        - 成功返回最小的未使用的文件描述符
        - 失败返回 -1，并设置 errno
int open(const char *pathname, int flags, mode_t mode);
    argument:
        - mode: 权限，可以用掩码(755)(八进制)的方式也可以用宏
                最终权限为 mode & ~umask
            - S_IRUSR: 用户读
            - S_IWUSR: 用户写
            - S_IXUSR: 用户执行
            - S_IRGRP: 组读
            - S_IWGRP: 组写          
            - S_IXGRP: 组执行         
            - S_IROTH: 其他读
            - S_IWOTH: 其他写
            - S_IXOTH: 其他执行

// creat() 函数是一个过时的系统调用
// 由于历史原因，creat() 函数仍然存在于一些系统中
int creat(const char *pathname, mode_t mocde);

int openat(int dirfd, const char *pathname, int flags);

int openat(int dirfd, const char *pathname, int flags, mode_t mode);
```

#### 2.2 创建文件

使用 `open` 函数，在标志位 `flags` 上附加 `O_CREAT`

#### 2.3 关闭文件

```c
#include <unistd.h>

// 关闭一个文件描述符，使文件描述符不再指向任何文件
// 进程关闭一个文件会释放它加在该文件上的所有记录锁
// 当一个进程终止时，内核会自动关闭它所有的打开的文件
int close(int fd);
    argument:
        - fd: 需要关闭的文件描述符

    return:
        - 成功返回 0
        - 失败返回 -1 并设置 errno
```

#### 2.4 定位读写位置

```c
#include <sys/types.h>
#include <unistd.h>

// 重新定位读/写文件偏移

// 除非打开文件时指定 O_APPEND，否则默认偏移量为 0

// 如果文件描述符指定一个管道、FIFO、网络套接字，则调用失败，返回 -1，并设置 errno

// 普通文件当前文件偏移量必须非负，但是某些设备可能有负的偏移量，
// 所以不能根据小于 0 来判断函数调用失败，而要判断是否等于 -1
// lseek 进行 I/O 操作

// 文件偏移量可以大于文件的当前长度，如果以 O_APPEND 标志打开文件，则此时 lseek 会被忽略
// 没有以 O_APPEND 标志打开文件，则文件系统会在偏移量之前创建一个空洞
// 空洞是文件中尚未写入数据的部分，写入空洞的数据会被填充为 0，并且文件系统不会实际分配磁盘空间
// 这种行为称为稀疏文件，允许程序在文件中创建逻辑上连续但物理上不连续的数据
off_t lseek(int fd, off_t offset, int whence);
    argument:
        - fd: 打开的文件的文件描述符
        - offset: 偏移量，单位字节
        - whence:
            - SEEK_SET: 设置为偏移字节
            - SEEK_CUR: 设置为其当前位置加上偏移字节
            - SEEK_END: 设置为文件的大小加上偏移字节
    return:
        - 成功返回从文件开头开始以字节为单位测量的结果偏移位置
        - 失败返回 -1，并设置 errno
```

```c
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 省略返回值判断
int main() {
    int fd = open("test.txt", O_RDWR | O_CREAT, 0644);

    // 写文件
    const char *str = "this is a test";
    write(fd, str, strlen(str));

    // 设置文件偏移量到文件开始第 5 个字节
    lseek(fd, 5, SEEK_SET);

    // 读文件
    char buf[128] = {};
    read(fd, buf, 128);
    printf("%s\n", buf);

    close(fd);
    return 0;
}

/*****************************/
is a test
```

#### 2.5 文件读

```c
#include <unistd.h>

// 读文件，读文件从当前偏移量开始
// 在成功返回之前，文件的当前偏移量会增加实际读到的字节数
// 实际读到的字节数小于期望读到的字节数的情况:
// 1. 从普通文件读可能在 count 之前到达文件末尾
// 2. 从终端设备读，通常一次只能读一行，终端默认是行缓冲
// 3. 从网络读，网络中的缓存机制
// 4. 从管道读
// 5. 从面向记录的设备读，一次最多返回一条记录
// 6. 当一个信号造成中断时，而已读了部分数据
ssize_t read(int fd, const void *buf, size_t count);
    arguments:
        - fd: 打开的文件的文件描述符
        - buf: 传出参数，存放读取内容的缓冲区的地址
        - count: 期望读到的字节数
    return:
        - 失败返回 -1，并设置 errno
        - 成功返回实际读到的字节数，读到末尾为 0
```

#### 2.6 文件写

```c
// 写文件
// 普通文件，写操作从文件当前文件偏移量开始

// 写入成功后，文件偏移量增加实际写入的字节数

// 如果文件指定 O_APPEND
// 则每次写入操作之前都会将文件偏移量设置在文件当前结尾
#include <unistd.h>

ssize_t write(int fd, const void *buf, size_t count);
    argument:
        - fd: 打开的文件的文件描述符
        - buf: 存放待写的数据内容的缓冲区的地址
        - count: 期望写入文件的字节数

    return:
        - 成功返回实际写入的字节数
        - 失败返回 -1，并设置 errno
```

#### 2.7 fcntl 函数

```cs
// 复制文件描述符
// 获取文件状态标志
// 设置文件状态标志
// 非阻塞 I/O
#include <unistd.h>
#include <fcntl.h>

int fcntl(int fd, int cmd, ... /* arg */ );
    arguement:
        - fd: 文件描述符
        - cmd: 操作命令
            - F_GETFL: 获取文件状态标志
            - F_SETFL: 设置文件状态标志，设置文件 flags
                ... arg:
                    必选项: 不可以被修改
                        - O_RDWR
                        - O_RDONLY
                        - O_WRONLY
                    可选: 可以修改
                        - O_APPEND: 追加数据
                        - O_NONBLOCK、O_NDELAY: 设置成非阻塞
                        - O_CREAT
                        - O_DIRECT
                        - O_DIRECTORY
                        - O_DSYNC
                        - O_EXCL
                        - O_LARGEFILE
                        - O_NOATIME
                        -
            - F_DUPFD: 复制文件描述符
            - F_GETFD: 获取文件描述符标志 flags，与 open 函数中传递的参数 flags 相同
            - F_SETFD: 设置文件描述符标志
            - F_GETLK: 获取文件锁
            - F_SETLK: 设置文件锁
            - F_SETLKW: 设置文件锁，如果锁不可用则阻塞
        - ...: 可变参数
    return:
        - -1: error, set errno
```

```c
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 省略返回值判断
int main() {
    int fd = open("test.txt", O_RDWR | O_CREAT, 0644);

    // 获取文件状态标志
    int fd_flags = fcntl(fd, F_GETFL);

    // 修改文件状态标志，增加 O_APPEND 标志位
    fcntl(fd, F_SETFL, fd_flags | O_APPEND);

    // 写文件
    write(fd, "test", 4);
    write(fd, "test", 4);

    // 设置文件偏移量到文件开始
    lseek(fd, 0, SEEK_SET);

    // 读文件
    char buf[128] = {};
    read(fd, buf, 128);
    printf("%s\n", buf);

    close(fd);
    return 0;
}

/*****************************/
testtest
```

### 3. 进程间文件共享

Unix 系统支持在不同进程间共享打开文件，内核使用 3 种数据结构描述打开文件。

![](./assets/%E8%BF%9B%E7%A8%8B%E9%97%B4%E6%96%87%E4%BB%B6%E5%85%B1%E4%BA%AB.png)

- 内核为每一个进程分配一个**进程表项**（所有进程表项构成进程表），内容为：
  - 文件描述符标志
  - 指向一个文件表项的指针
- 内核为每个打开的文件分配一个**文件表项**（所有的文件表项构成文件表），内容为：
  - 文件状态标志（读、写、添加、同步和阻塞等）
  - 当前文件偏移量
  - 指向该文件 v 节点的指针
- 每一个打开的文件或设备都有一个 **v 节点结构**。内容为：
  - 文件类型和对此文件进行操作函数的指针
  - 对于大多数文件，v 节点还包含该文件的 i 节点，如 i 节点包含了文件所有者、文件长度、指向文件实际数据在磁盘上所在位置的指针等，这些信息是打开文件时从磁盘读入内存的，v 节点结构和 i 节点结构实际上代表了文件的实体，Linux 没有使用 v 节点，而是使用 i 节点结构，虽然两者实现不同，但是在概念上，两者都指向文件系统特有的 i 节点结构

假设进程 A 打开文件 `file1`，返回文件描述符 3；进程 B 也打开文件 `file1`，返回文件描述符 4；

![](./assets/%E8%BF%9B%E7%A8%8B%E9%97%B4%E6%96%87%E4%BB%B6%E5%85%B1%E4%BA%AB2.png)

内核在文件表上新增两个表项：

- 这两个文件表项指向同一个 v 节点表项
- 进程 A、B 各自的文件描述符表项分别指向这两个文件表项，因此每个进程都有独立的当前文件偏移量

对文件操作的结果：

- 每次 `write` 之后，在文件表项中的当前文件偏移量增加所写入的字节数，若 `write` 导致当前文件偏移量超出当前文件长度，则修改 i 节点的当前文件长度，设为当前文件偏移量
- 若用 `O_APPEND` 标志打开一个文件，则相应标志也设置到文件表项的文件状态标志中，每次对具有 `O_APPEND` 标志的文件 `write` 操作时，文件表项中的当前文件偏移量首先被置为 i 节点中的文件长度
- 若用 `lseek` 定位到文件当前尾端，则文件表项中当前文件偏移量置为 i 节点中的文件长度

### 4. 原子操作

> 多个进程写同一个文件时，可能会产生预想不到的结果，为了避免这种情况，需要理解原子操作

多个进程同时追加写一个文件时，如果通过 `lseek` 到末尾然后 `write` 可能出现问题：因为*先定位到文件尾端，然后写*，并不是一个原子操作，如果先执行两个进程的 `lseek`，然后执行 `write`，就会出现问题

Unix 提供了一种原子操作方法：通过 `O_APPEND` 选项打开文件，此时内核调用 `write` 执行写操作之前，都将进程的当前偏移量设置到该文件的末尾，于是就不需要执行 `lseek` 定位操作

#### 定位读和定位写

```c
#include <unistd.h>

// 调用 pwrite 相当于优先调用 lseek 再调用 read
// 调用 pwrite 时无法中断其定位和读操作
// 不会更新当前文件偏移量
ssize_t pwrite(int fd, const void *buf, size_t count, off_t offset);
    argument:
        - fd: 打开的文件描述符
        - buf: 写到文件的数据的缓冲区
        - count: 预期写入文件的字节数
        - offset: 从文件指定偏移量开始执行 write

    return: 
        - 成功返回写入的字节数
        - 失败返回 -1，设置 errno

// 调用 pread 相当于优先调用 lseek 再调用 read
// 调用 praed 时无法中断其定位和读操作
// 不会更新当前文件偏移量
ssize_t pread(int fd, void *buf, size_t count, off_t offset);
    argument:
        - fd: 打开的文件描述符
        - buf: 读出数据存放的缓冲区
        - count: 预期读出文件的字节数
        - offset: 从文件指定偏移量开始执行 read

    return:
        - 成功返回读取的字节数
        - 失败返回 -1， 并设置 errno
```

### 5. 数据同步

Unix 内核中有**缓冲区高速缓存**或**页高速缓存**，大多数磁盘 I/O 都通过缓冲区进行，当向文件写入数据时，内核通常都会先将数据复制到缓冲区中，然后排入队列，再写入磁盘，这种方式称为**延迟写**

两种方式会将缓冲区中的数据写入磁盘：

1. 当内核需要重用缓冲区来存放其他数据时，会将所有延迟写的数据写入磁盘
2. 调用 `sync`、`fsync`、`fdatasync` 来显式的将所有延迟写的数据写入磁盘

```c
#include <unistd.h>
// 将文件系统缓存提交到磁盘

// sync（update 守护进程会周期性(一般每隔30s)的调用 sync 函数。命令 sync 也会调用 sync 函数）：
// 将所有修改过的块缓冲区排入写队列
// 不等待实际写磁盘操作结束
void sync(void);

// 和 sync 类似
// 只对 fd 指定的单个文件起作用
// 不等待实际写磁盘操作结束
int syncfs(int fd);

#include <unistd.h>
// 将文件的内核状态与存储设备同步

// 只对 fd 指定的单个文件起作用
// 等待写磁盘操作结束才返回
// 会同时更新文件的属性
int fsync(int fd);
    argument:
        - fd: 指定写回的文件

    return:
        - 成功返回 0
        - 失败返回 -1，并设置 errno

// 只对 fd 指定的单个文件起作用
// 只影响文件的数据部分
// 等待写磁盘操作结束才返回
int fdatasync(int fd);
```
