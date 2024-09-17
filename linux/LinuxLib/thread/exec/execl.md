```c
/*
    // 标准 C 系统函数
    #include <unistd.h>

    extern char **environ;

    // l 是 list，表示使用列表传参
    int execl(const char *pathname, const char *arg, ..., (char *) NULL);
        argument:
            - pathname: 需要指定的执行的文件的路径
            - arg: 执行可执行程序需要的参数列表
                - arg0: 可以写可执行程序的名称 (作用不大，显示在 ps aux 中 COMMAND
                - arg...: 程序执行所需要的参数列表，必须以 NULL 结尾
        return: 调用错误才有 -1 返回值，set errno
 */

#include <unistd.h>
#include <stdio.h>

int main() {
    /*
        创建子进程，在子进程中执行 exec 函数族中的函数
        exec 函数族会将进程代码进行替换，在父进程中执行 exec 函数族会将父进程中的代码也替换了
     */
    int s_pid = fork();
    if (0 == s_pid) {
        /* 子进程 */
        /* 执行自己的可执行文件 */
        // execl("../get_pid/get_pid.out", "get_pid.out", NULL);
        /* 执行系统的可执行文件 */
        execl("/bin/ps", "ps", "aux", NULL); // 需要写绝对路劲，因为 execl 不会到环境变量中去查找指定文件
        printf("child  process id: %d\n", getpid()); // 如果 execl 函数调用成功，子进程代码被替换，这条语句不运行，调用失败执行这条语句
    }
    else if (0 < s_pid) {
        /* 父进程 */
        // execl("../get_pid/get_pid.out", "get_pid.out", NULL); // bad，主进程代码替换
        printf("parent process id: %d\n", getpid());
        sleep(1);
    }

    /* 只有父进程运行，子进程代码已被替换 */
    for (int i = 0; i < 10; ++i) {
        printf("i = %d process id: %d\n", i, getpid());
    }
    return 0;
}
```

