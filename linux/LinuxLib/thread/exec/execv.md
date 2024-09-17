```c
/*
    #include <unistd.h>

    // v 是 vector，表示使用矢量传参
    int execv(const char *pathname, char *const argv[]);
        argument:
            - pathname: 可执行程序路径
            - argv[]: 字符串数组
        return: 调用错误才有 -1 返回值，set errno
 */

#include <unistd.h>
#include <stdio.h>

int main() {
    int s_pid = fork();

    if (0 == s_pid) {
        /* 子进程 */
        char* argv[] = { "get_pid.out", NULL }; // 和 execl 一样的规则
        int ret = execv("../get_pid/get_pid.out", argv);
        if (-1 == ret) {
            perror("execv");
        }
        else if (0 < s_pid) {
            printf("parent process id: %d\n", getpid());
        }
    }
    return 0;
}
```

