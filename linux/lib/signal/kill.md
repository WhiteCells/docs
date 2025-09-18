```c
/*
    // 将信号发送到任意进程或进程组
    #include <sys/types.h>
    #include <signal.h>

    int kill(pid_t pid, int sig);
        argument:
            - pid: 需要发送的进程的 id
                - > 0: 将 sig 发送到 ID 为 pid 的进程 
                - 0: 将 sig 发送到调用进程的进程组中的每个进程
                - -1: 将 sig 发送到有权限接受 sig 的进程
                - < -1: 将 sig 发送到进程组中 ID 为 -pid 的每个进程
            - sig: 需要发送的信号的编号或者宏值 
                - sig 的编号
                - sig 的宏值 (不同的平台通用)
                - 0: 不发送 sig

        return: 
            - 0: success
            - -1: error, set errno
 */
```

```c
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    pid_t s_pid = fork();

    if (0 == s_pid) {
        for (int i = 0; i < 5; ++i) {
            printf("child process\n");
            sleep(1);
        }
    } else if (0 < s_pid) {
        printf("parent process\n");
        sleep(2);
        int ret = kill(s_pid, SIGINT);
        if (-1 == ret) {
            perror("kill");
            exit(0);
        }
        puts("kill child process now");
    } else if (-1 == s_pid) {
        perror("fork");
        exit(0);
    }

    return 0;
}
```
