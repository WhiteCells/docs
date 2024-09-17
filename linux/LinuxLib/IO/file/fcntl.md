```c
/*
    // 复制文件描述符
    // 设置 / 获取文件的状态标志
    // 设置文件状态标志
    // 获取文件状态标志
    // 非阻塞 I/O
    #include <unistd.h>
    #include <fcntl.h>

    int fcntl(int fd, int cmd, ... );
        arguement:
            - fd: 文件描述符
            - cmd: 操作命令
                - F_DUPFD: 复制文件描述符（dup）
                - F_GETFD: 获取文件描述符标志 flags，与 open 函数中传递的参数 flags 相同（get）
                - F_SETFD: 设置文件描述符标志
                - F_GETFL: 获取文件状态标志
                - F_SETFL: 设置文件状态标志，设置文件 flags（set）
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
                - F_GETLK: 获取文件锁
                - F_SETLK: 设置文件锁
                - F_SETLKW: 设置文件锁，如果锁不可用则阻塞
            - ...: 可变参数
        return:
            - -1: error, set errno
 */
```

```c
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main() {
    // int fd1 = open("../word.txt", O_RDONLY); // 可读权限
    // if (-1 == fd1) {
    //     perror("open ../word.txt");
    //     return -1;
    // }
    // /* 复制文件描述符 */
    // int fd1_copy = fcntl(fd1, F_DUPFD);
    // printf("fd1 = %d fd1_copy = %d\n", fd1, fd1_copy);
    // close(fd1);

    int fd = open("../word3.txt", O_RDWR | O_CREAT, 0775);
    if (-1 == fd) {
        perror("open");
        return -1;
    }

    /* 获取文件状态标志 */
    int file_flag = fcntl(fd, F_GETFL); // 当前文件的 flag
    file_flag |= O_APPEND; // 新的 flag

    /* 修改文件状态标志 */
    int ret = fcntl(fd, F_SETFL, file_flag); // 原先 flag | O_APPEND
    if (-1 == ret) {
        perror("fcntl");
        return -1;
    }

    /* 向文件中写入 */
    char* buf = "test";
    int len = write(fd, buf, strlen(buf));
    if (0 > len) {
        perror("write");
        return -1;
    }

    close(fd);

    return 0;
}
```

