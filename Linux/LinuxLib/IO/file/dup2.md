```c
/*
    // 重定向文件描述符
    #include <unistd.h>

    int dup2(int oldfd, int newfd);
        argument:
            - oldfd: 文件描述符，必须是有效的
            - newfd: oldfd 指向的新的文件描述符，如果与 oldfd 则无效果，newfd 不再指向文件
        return:
            - fd: 新的文件描述符
 */
```

```c
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main() {
    int fd1 = open("../word3.txt", O_RDWR | O_CREAT, 0664);
    if (-1 == fd1) {
        perror("open ../word.txt");
        return -1;
    }
    printf("fd1 = %d\n", fd1);

    int fd2 = open("../word.txt", O_RDWR | O_CREAT, 0664);
    if (-1 == fd2) {
        perror("open ../word3.txt");
        return -1;
    }
    printf("fd2 = %d\n", fd2);

    /* 重定向 fd2 */
    // fd1 是要被复制的文件描述符，fd2 是新的文件描述符。这个函数会关闭原始的 fd2，然后将 fd1 复制到 fd2
    int fd3 = dup2(fd1, fd2); // fd2 不再指向 word.txt 而是指向 word3.txt
    if (-1 == fd3) {
        perror("dup2");
        return -1;
    }
    printf("fd1 = %d\n", fd1);
    printf("fd2 = %d\n", fd2);
    printf("fd3 = %d\n", fd3);

    /* 向 fd2 指向文件写入输入 */
    char buf1[] = "this paragraph will be written to the word3.txt file";
    int ret = write(fd2, buf1, strlen(buf1));
    if (-1 == ret) {
        perror("write");
        return -1;
    }

    /* 读取 word3.txt */
    // ?? bug
    char buf2[1024] = { 0 };
    while (0 < read(fd3, buf2, sizeof(buf2))) {
        printf("%s", buf2);
    }

    close(fd1);
    close(fd2);
    /* fd3 返回值不需要操作 */
    return 0;
}
```

