```c
/*
    // 创建目录
    #include <sys/stat.h>
    #include <sys/types.h>

    int mkdir(const char *pathname, mode_t mode);
        argument:
            - pathname: 要创建的目录的路径名
            - mode: 新目录的访问权限 mode & ~umask & 0777 最终权限
        return:
            -  0: success
            - -1: error
 */
```

```c
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int ret = mkdir("test-dir", 0777);
    if (-1 == ret) {
        perror("mkdir");
        return -1;
    }
    printf("successfully created folder\n");
    return 0;
}
```

