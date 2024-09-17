```c
/*
    // 缩进或者扩展文件至指定大小
    #include <unistd.h>
    #include <sys/types.h>

    int truncate(const char *path, off_t length);
        argument:
            - path: 文件路径
            - length: 指定后的文件大小
        return:
            -  0: success
            - -1: error，并设置 errno
            
    int ftruncate(int fd, off_t length);
 */
```

```c
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main() {
    /* 获取文件状态 */
    struct stat file_stat;
    int ret1 = stat("option.txt", &file_stat);
    if (-1 == ret1) {
        perror("stat");
        return -1;
    }
    printf("file size: %ld\n", file_stat.st_size);

    /* 修改文件大小 */
    printf("enter the file size you want to modify: ");
    unsigned size = 0;
    scanf("%u", &size);
    int ret2 = truncate("option.txt", size);
    if (-1 == ret2) {
        perror("truncate");
        return -1;
    }

    /* 获取文件状态 */
    int ret3 = stat("option.txt", &file_stat);
    if (-1 == ret3) {
        perror("stat");
        return -1;
    }
    printf("file size: %ld\n", file_stat.st_size);

    return 0;
}
```

