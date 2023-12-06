```c
/*
    // 创建有名管道
    #include <sys/types.h>
    #include <sys/stat.h>

    int mkfifo(const char *pathname, mode_t mode);
        argument:
            - pathname: 创建有名管道的路径
            - mode: 文件的权限
        
        return:
            - 0 : 调用成功
            - -1: 调用失败，并设置错误号
 */
```

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int ret = mkfifo("fifo1", 0666);
    if (-1 == ret) {
        perror("mkfifo fifo1");
        exit(0);
    }
    return 0;
}
```

