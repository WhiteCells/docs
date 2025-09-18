```c
/*
    // 等待任意一个进程结束，任意一个进程结束，该函数会回收子进程资源
    #include <sys/types.h>
    #include <sys/wait.h>

    pid_t wait(int *wstatus);
        argument:
            - wstatus: 传出参数，进程退出时的状态信息。传入一个 int 类型地址
        return:
            - child pid: 成功返回被回收的子进程
            - -1: 所有子进程结束，或者调用函数失败
        // 调用 wait 函数的进程会被挂起（阻塞），直到它的一个子进程退出或者收到一个不能被忽略的信号时才被唤醒（相当于继续执行）
        // 没有子进程，立刻返回 -1

    // 退出信息相关宏函数
    WIFEXITED(status)    // 非 0，进程正常退出
    WEXITSTATUS(status)  // 上宏非 0，获取进程退出的状态（exit 的参数）

    WIFSIGNALED(status)  // 非 0，进程异常终止
    WTERMSIG(status)     // 上宏非 0，获取使进程终止的信号编号

    WIFSTOPED(status)    // 非 0，进程处于暂停状态
    WSTOPSIG(status)     // 上宏非 0，获取使进程暂停的信号编号
    WIFCONTINUED(status) // 非 0，进程暂停后已经继续运行
 */
```

```c
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t s_pid;

    /* 创建 5 个子进程 */
    for (int i = 0; i < 5; ++i) {
        s_pid = fork();
        /* 防止子进程再创建子进程 */
        if (0 == s_pid) {
            break;
        }
    }

    if (0 == s_pid) {
        printf("this is child process id: %d\n", getpid());
    } else if (0 < s_pid) {
        printf("---this is parent process, pid: %d\n", getpid());
        while (1) {
            int wstatus = 0;
            int ret = wait(&wstatus); // 返回被回收的子进程的 ID
            /* 进程回收完成 */
            if (-1 == ret) {
                printf("child process recycling completed\n");
                break;
            }
            /* 进程是否正常退出 */
            if (WIFEXITED(wstatus)) {
                /* 进程正常退出，打印进程退出的状态 */
                printf("process %d exited normally, exit status: %d\n", ret, WEXITSTATUS(wstatus));
            }
            if (WIFSIGNALED(wstatus)) {
                /* 进程是否异常终止，打印使进程异常终止的信号编号 */
                printf("process %d terminated abnormally, signal num: %d\n", ret, WTERMSIG(wstatus));
            }
            if (WIFSTOPPED(wstatus)) {
                /* 进程处于暂停状态，打印使进程暂停的信号编号 */
                printf("process %d pause, signal num: %d\n", ret, WSTOPSIG(wstatus));
            }
            printf("recycled child process id: [%d], ppid: [%d]\n", ret, getpid());
            sleep(1);
        }
    }
    return 0;
}
```

