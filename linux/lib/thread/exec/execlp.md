```c
/*
    // 标准 C 系统函数
    #include <unistd.h>

    extern char **environ;

    // l 是 list，表示使用列表传参，p 是 path，表示使用环境变量查找可执行文件
    int execlp(const char *file, const char *arg, ..., (char *) NULL);
        argument:
            - file: 需要指定的执行的文件的路径
            - arg: 执行可执行程序需要的参数列表
                - arg0: 可以写可执行程序的名称
                - arg...: 程序执行所需要的参数列表，必须以 NULL 结尾
        return: 调用错误才有 -1 返回值，set errno
 */

#include <unistd.h>
#include <stdio.h>

int main() {
    int s_pid = fork();

    if (0 == s_pid) {
        /* 子进程 */
        /* 执行系统的可执行程序 */
        execlp("ps", "ps", "aux", NULL);

        // int ret = execlp("../get_pid/get_pid.out", "git_pid.out", NULL);
        // if (-1 == ret) {
        //     perror("execlp");
        // }
    }
    else if (0 < s_pid) {
        /* 父进程 */
        printf("parent process id: %d\n", getpid());
        for (int i = 0; i < 10; ++i) {
            printf("i = %d, process id: %d\n", i, getpid());
        }
    }

    return 0;
}
```

