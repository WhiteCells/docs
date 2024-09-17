```c
/*
    #include <unistd.h>

    long fpathconf(int fd, int name);
        argument:
            - fd:
            - name:
                - _PC_LINK_MAX: 指向文件的最大链接数
                - _PC_MAX_CANON: 格式化输入行的最大长度
                - _PC_MAX_INPUT: 输入行的最大长度
                - _PC_NAME_MAX: 允许进程创建的目录路径或文件名的最大长度
                - _PC_PATH_MAX: 当路径或文件描述符是当前工作目录时，相对路径名的最大长度
                - _PC_PIPE_BUF: 可以原子方式写入 FIFO 管道的最大字节数
                - _PC_CHOWN_RESTRICTED: 是否对chown函数有限制
                - _PC_NO_TRUNC: 是否对文件名截断有限制
                - _PC_VDISABLE: 终端特殊字符的禁用值
        return: 对应限制类型的值，如果出错则返回-1
        
    long pathconf(const char *path, int name);
 */
```

```c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int pipe_fd[2];
    int ret = pipe(pipe_fd);

    if (-1 == ret) {
        perror("pipe");
        return -1;
    }

    /* 获取管道大小 */
    long pipe_buf_size = fpathconf(pipe_fd[0], _PC_PIPE_BUF);
    printf("pipe buf size: %ld\n", pipe_buf_size);
    return 0;
}


```

