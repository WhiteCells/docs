```c
/*
    // 读文件
    #include <unistd.h>

    ssize_t read(int fd, const void *buf, size_t count);
        arguments:
            - fd: 文件描述符
            - buf: 需要读取数据存放的地方，数组地址，传出参数
            - count: 指定的数组的大小
        return:
            - -1: On error, -1 is returned, and errno is set appropriately，设置 perror
            - >0: 返回实际的读取到的字节数
            - 0 : 已经读取到文件末尾
 */
```

```c
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd = open("../word.txt", O_RDONLY, 0775);

    if (-1 == fd) {
        perror("open");
        return -1;
    }

    char buf[1024] = { 0 };
    while (read(fd, buf, 1024) > 0) {
        printf("%s\n", buf);
    }

    close(fd);
    return 0;
}

```

