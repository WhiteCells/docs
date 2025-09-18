```c
/*
    #include <unistd.h>
    // unix 系统函数

    //  execvpe 函数是 POSIX 标准中定义的函数，但并不是标准 C 库中的一部分。它可能不被所有的编译器支持
    //  v 是 vector，表示使用矢量传参，e 是 environment，表示使用额外的环境变量设置。
    int execve(const char *pathname, char *const argv[], char *const envp[]);
        argument:
            - pathname: 可执行文件路径
            - argv:
 */

#include <unistd.h>
#include <stdio.h>

int main() {
    int s_pid = fork();

    if (0 == s_pid) {
        /* 子进程 */
        char* argv[] = { "ps", "aux", NULL };
        char* envp[] = { "ps=/bin/ps", NULL };
        int ret = execve("ps", argv, envp); // ?? bug
        if (-1 == ret) {
            perror("execve");
        }
    }
    else if (0 < s_pid) {
        printf("parent process id: %d\n", getpid());
    }
    return 0;
}
```

