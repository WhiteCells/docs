```c
/*
    #include <stdio.h>

    int fseek(FILE *stream, long offset, int whence);
        argument:
            - stream:
            - offset:
            - whence:
        return:

    #include <sys/types.h>
    #include <unistd.h>

    off_t lseek(int fd, off_t offset, int whence);
        argument:
            - fd: 文件描述符
            - offset: 偏移量
            - whence:
                - SEEK_SET: 设置文件指针偏移量
                - SEEK_CUR: 设置偏移量，当前位置加上 offset 的值
                - SEEK_END: 设置偏移量，文件大小加上 offset 的值
        return: 文件指针的最终位置
            - successful: returns the resulting offset location as measured in bytes from the beginning of the file
            - error: the value (off_t) -1 is returned and  errno is set to indicate the error

        // 作用:
            1. 移动文件指针到头文件 lseek(fd, 0, SEEK_SET);
            2. 获取当前文件指针的位置 lseek(fd, 0, SEEK_CUR);
            3. 获取文件长度 lseek(fd, 0, SEEK_END);
            4. 拓展文件长度 lseek(fd, 10, SEEK_END); // 文件拓展 10 字节（需要写一次数据），下载的时候先创建文件，在修改文件
 */
```

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd = open("word.txt", O_RDWR);
    if (-1 == fd) {
        perror("open");
        return -1;
    }

    printf("当前文件指针位置: %ld\n", lseek(fd, 0, SEEK_CUR)); // 0

    /* 移动文件指针到头文件 */
    lseek(fd, 0, SEEK_SET);

    /* 获取当前文件指针的位置 */
    printf("当前文件指针位置: %ld\n", lseek(fd, 0, SEEK_CUR)); // 0
    char buf[23] = "这是新加的内容";
    write(fd, buf, sizeof(buf));

    /* 获取当前文件指针的位置 */
    printf("当前文件指针位置: %ld\n", lseek(fd, 0, SEEK_CUR)); // 23

    /* 获取文件长度 */
    printf("%ld\n", lseek(fd, 0, SEEK_END)); // 452

    /* 拓展文件长度 */
    long int ret = lseek(fd, 10, SEEK_END);
    if (-1 == ret) {
        perror("lseek");
        return -1;
    }
    // 需要向文件中写入一次数据才能成功拓展文件
    write(fd, " ", 1);
    printf(" 文件拓展之后的长度: %ld\n", ret); // 463

    return 0;
}
```

