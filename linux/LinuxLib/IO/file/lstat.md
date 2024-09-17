```c
/*
    // 用于获取文件或符号链接的状态信息，获取软链接文件的信息
    // ln -s word.txt word2.txt // 软链接
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>

    int lstat(const char *pathname, struct stat *statbuf);
        argument:
            - pathname: 操作文件路径，当 path 是符号链接时，它返回符号链接本身的信息，而不是符号链接指向的文件的信息
            - statbuf: 结构体之变量，是一个传出参数，保存获取到的文件的信息
        return:
            - 0 : On success, 0 is returned
            - -1: On error, -1 is returned, and errno is set appropriately

 */
```

```c


#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    struct stat file_stat;

    int ret = lstat("../word2.txt", &file_stat);

    if (-1 == ret) {
        perror("stat");
        return -1;
    }

    printf("word2.txt size: %ld byte\n", file_stat.st_size); // 返回符号链接本身的信息

    return 0;
}


```

