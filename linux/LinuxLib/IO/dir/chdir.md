```c
/*
    // 修改进程当前工作目录为指定的目录路径
    #include <unistd.h>

    int chdir(const char *path);
        argument:
            - path: 路径
        return:
            -  0: success
            - -1: error, set errno
    int fchdir(int fd);
 */
```

```c
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main() {
    /* 输出进程当前工作区路径 */
    char buf1[1024] = { 0 };
    char* pathname1 = getcwd(buf1, sizeof(buf1));
    if (NULL == pathname1) {
        perror("getpwd");
        return -1;
    }
    printf("current working directory: %s\n", buf1);

    /* 修改进程工作目录 */
    int ret1 = chdir("test2-dir");
    if (-1 == ret1) {
        perror("chdir");
        return -1;
    }
    printf("successfully changed folder\n");

    /* 进程当前目录创建文件 */
    int fd = open("test2-file.txt", O_RDWR | O_CREAT, 0775);
    if (-1 == fd) {
        perror("open");
        return -1;
    }
    close(fd);

    /* 判断新创建的文件是否创建成功 */
    int ret2 = access("test2-file.txt", F_OK);
    if (-1 == ret2) {
        perror("access");
        return -1;
    }
    printf("file exsits\n");

    /* 输出进程当前工作区路径 */
    char buf[1024] = { 0 };
    char* pathname = getcwd(buf, sizeof(buf));
    if (NULL == pathname) {
        perror("getpwd");
        return -1;
    }
    printf("current working directory: %s\n", buf);

    return 0;
}
```

