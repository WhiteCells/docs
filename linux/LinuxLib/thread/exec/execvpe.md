```c
/*
    #include <unistd.h>

    // v 是 vector，表示使用矢量传参，p 是 path，表示使用环境变量查找可执行文件，e 是 environment，表示使用额外的环境变量
    int execvpe(const char *file, char *const argv[], char *const envp[]);
        argument:
            - file:
            - argv:
            - envp:
        return:
 */

#include <unistd.h>
#include <stdio.h>

int main() {
    int s_pid = fork();

    if (0 == s_pid) {
        /* 子进程 */
        char* envp[] = { "get_pid.out", NULL };
        char* argv[] = { NULL };
        int ret = execvpe("../get_pid/get_pid.out", argv, envp);
    }
    else if (0 < s_pid) {
        printf("this is parent process id: %d\n", getpid());
    }
    return 0;
}
```

