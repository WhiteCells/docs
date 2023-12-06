

```c
/*
    // 退出进程，标准 C 库
    // 刷新 I/O 缓冲，关闭文件描述符
    #include <stdlib.h>
    
    void exit(int status);
        argument:
            - status: 进程退出时的一个状态信息，父进程在回收子进程资源的时候可以获取到

 */
```

```c
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    printf("111\n");
    printf("222");
    exit(0);
}
```

