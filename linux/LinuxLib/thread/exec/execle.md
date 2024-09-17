```c
/*
    // 标准 C 系统函数
    #include <unistd.h>

    extern char **environ;

    // l 是 list，表示使用列表方式传参，e 是 environment，表示使用额外的环境变量
    int execle(const char *pathname, const char *arg, ..., (char *) NULL, char *const envp[]);
        argument:
            - pathname: 需要指定的执行的文件的路径
            - arg: 执行可执行程序需要的参数列表
                - arg0: 可以写可执行程序的名称
                - arg...: 程序执行所需要的参数列表，必须以 NULL 结尾
            - envp[]: 用于设置新程序的环境变量字符串数组
        return: 调用错误才有 -1 返回值，set errno
 */

#include <unistd.h>
#include <stdio.h>

int main() {
    int s_pid = fork();

    if (0 == s_pid) {
        /* 子进程 */
        char* envp[] = { "/bin/ps/", NULL };
        int ret = execle("ps", "ps", "aux", NULL, envp); // ?? bug
        if (-1 == ret) {
            perror("execle");
        }
    }
    else if (0 < s_pid) {
        /* 父进程 */
        printf("parent process id: %d\n", getpid());
    }

    return 0;
}
```

