```c
/*
    #include <sys/types.h>
    #include <sys/wait.h>

    // 回收指定进程号的子进程
    // 设置是否阻塞
    pid_t waitpid(pid_t pid, int *wstatus, int options);
        argument:
            - pid:
                - (pid > 0): 回收指定进程 pid 的子进程
                - (pid == 0): 回收当前进程组的所有子进程
                - (pid == -1): 回收所有子进程，相当于 wait()
                - (pid < -1): 某个进程组的组 id 的绝对值，回收进程组的组中的子进程
            - wstatus: 传出参数, 进程退出时的状态信息
            - options:
                - 0: 阻塞
                - WNOHANG: 非阻塞
        return:
            - > 0: 返回子进程 ID
            - = 0: (options = WNOHANG) 时使用) 还有子进程未退出
            - -1 : 没有子进程 or 错误, set errno
            
    // 退出信息相关宏函数
    WIFEXITED(status)    // 非 0, 进程正常退出
    WEXITSTATUS(status)  // 上宏非 0, 获取进程退出的状态（exit 的参数）

    WIFSIGNALED(status)  // 非 0, 进程异常终止
    WTERMSIG(status)     // 上宏非 0, 获取使进程终止的信号编号

    WIFSTOPED(status)    // 非 0, 进程处于暂停状态
    WSTOPSIG(status)     // 上宏非 0, 获取使进程暂停的信号编号
    WIFCONTINUED(status) // 非 0, 进程暂停后已经继续运行
*/
```

```c
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t s_pid;

    for (int i = 0; i < 5; ++i) {
        s_pid = fork();
        if (0 == s_pid) {
            break;
        }
    }
    if (0 == s_pid) {
        /* 子进程 */
        printf("this is child process, pid: %d\n", getpid());
        sleep(1);
    } else if (0 < s_pid) {
        /* 父进程回收子进程 */
        while (1) {
            int wstatus = 0;
            int ret = waitpid(-1, &wstatus, 0); // 阻塞，等待子进程执行完
            // int ret = waitpid(-1, &wstatus, WNOHANG); // 无阻塞，父进程不挂起
            if (-1 == ret) {
                /* 子进程回收完成 */
                printf("child process recycling completed\n");
                break;
            } else if (0 == ret) {
                /* 还有子进程存在 */
                printf("there are also child processes\n"); // 如果阻塞情况，该语句不执行
                continue;
            } else if (0 < ret) {
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
            }
            sleep(1);
        }
    }
    return 0;
}
```

