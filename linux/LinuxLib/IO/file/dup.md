```c
/*
    // 赋值文件描述符，指向同一个文件
    // 从空闲的文件描述符表中找到最小的最新的拷贝的文件描述符
    #include <unistd.h>

    int dup(int oldfd);
        argument:
            - oldfd: 需要复制的文件描述符
        return: On success, these system calls return the new file descriptor.  On error, -1 is returned, and errno is set appropriately.
            -  int: new file descriptor
            - -1: error, set errno
 */
```

```c
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>

int main() {

    int fd = open("../word.txt", O_RDONLY);
    if (-1 == fd) {
        perror("open");
        return -1;
    }
    printf("fd = %d\n", fd); // 3

    int fd_copy1 = dup(fd);
    if (-1 == fd_copy1) {
        perror("dup");
        return -1;
    }
    printf("fd_copy = %d\n", fd_copy1); // 4

    /* 新复制的文件描述符，会在文件描述符表中找最小的最新的文件描述符拷贝 */
    int fd_copy2 = dup(fd_copy1);
    if (-1 == fd_copy2) {
        perror("dup");
        return -1;
    }
    printf("fd_copy2 = %d\n", fd_copy2); // 3

    close(fd);
    close(fd_copy1);
    close(fd_copy2);
    return 0;
}
```

