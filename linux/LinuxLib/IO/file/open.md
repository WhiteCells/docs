```c
/*
    // 打开一个已经存在的文件
    #include <sys/types.h> // 它定义了一些基本的系统数据类型
    #include <sys/stat.h> // 用于访问和操作文件状态
    #include <fcntl.h> // 包含了文件控制相关的函数、宏和常量的定义

    int open(const char *pathname, int flags, ...);
        argument:
            - pathname: 打开的文件路径
            - flags: 对文件的操作权限设置及其他设置
                - O_RDONLY
                - O_WRONLY
                - O_RDWR
        return: 文件描述符, 调用失败返回 -1

    errno: 属于 Linux 系统函数库, 库中的一个全局变量, 记录的是错误号

    // 打印 error 对应的错误描述
    #include <stdio.h>

    void perror(const char *s);
        argument:
            - s: 用户描述, 比如 openerror, 最终输出内容为 openerror: <实际错误描述>

    // 关闭文件
    #include <unistd.h>

    int close(int fd);
        argument: fd 文件描述符
        return: 调用失败返回 -1
 */
```

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd = open("./word.txt", O_RDONLY);
    if (-1 == fd) {
        perror("open");
        return -1;
    }
    close(fd);

    return 0;
}
```

