```c
/*
    // 写文件
    #include <unistd.h>

    ssize_t write(int fd, const void *buf, size_t count);
        arguments:
            - fd: 文件描述符
            - buf: 要往磁盘读入的数据，数组地址，传出参数
            - count: 要写的数据的实际大小
        return:
            - error:
                - -1: On error, -1 is returned, and errno is set appropriately，设置 perror
            - success:
                - > 0: 返回实际的写入文件的字节数
                - = 0: 没有内容写道文件
 */
```

```c
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd = open("word.txt", O_RDWR);

    if (-1 == fd) {
        perror("open");
        return -1;
    }

    char buf[1024] = { 0 };
    fgets(buf, sizeof(buf), stdin);
    write(fd, buf, strlen(buf));

    close(fd);
    return 0;
}


```

