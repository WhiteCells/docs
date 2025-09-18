```c
/*
    // 判断进程对某个文件是否有某个权限，或者判断文件是否存在
    #include <unistd.h>

    int access(const char *pathname, int mode);
        argument:
            - pathname: 文件路径
            - mode:
                 - R_OK: 是否有读权限
                 - W_OK: 是否有写权限
                 - X_OK: 是否有可执行权限
                 - F_OK: 是否存在
        return:
            -  0: success
            - -1: error On error (at least one bit in mode asked for a permission that is denied, or moist, or some other error occurred), -1 is returned, and errno is set appropriately.
 */
```

```c
#include <unistd.h>
#include <stdio.h>

int main() {
    int ret = access("../word.txt", F_OK);

    if (-1 == ret) {
        perror("access");
        return -1;
    }
    printf("file exist\n");

    return 0;
}
```

