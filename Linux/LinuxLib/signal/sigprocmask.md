```c
/*
    // 将自定义信号集中的数据设置到内核中
    #include <signal.h>

    // Prototype for the glibc wrapper function
    int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
        argument:
            - how: 假设内核中阻塞信号集是 mask
                - SIG_BLOCK: mask |= set
                - SIG_UNBLOCK: mask &= ~set
                - SIG_SETMASK: 替换
            - set: 设置到内核中的自定义信号集
            - oldset: 传出参数, 保存之前内核中阻塞信号集的集状态, 除非传入 NULL

        return:
            - 0: success
            - -1: error, set errno
                - EFAULT
                - EINVAL

    // Prototype for the underlying system call
    int rt_sigprocmask(int how, const kernel_sigset_t *set,
                        kernel_sigset_t *oldset, size_t sigsetsize);

    // Prototype for the legacy system call (deprecated)
    int sigprocmask(int how, const old_kernel_sigset_t *set,
                    old_kernel_sigset_t *oldset);
 */
```

```c
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    sigset_t sset;

    sigemptyset(&sset);

    sigaddset(&sset, SIGINT);
    sigaddset(&sset, SIGQUIT);

    // 修改内核中的阻塞信号集
    sigprocmask(SIG_BLOCK, &sset, NULL);

    while (1) {
        // 获取未决信号集
        sigset_t psset;
        sigemptyset(&psset);
        sigpending(&psset);
        for (int i = 1; i <= 32; ++i) {
            int ret = sigismember(&psset, i);
            if (1 == ret) {
                printf("1");
            } else if (0 == ret) {
                printf("0");
            } else {
                perror("sigismement");
                exit(0);
            }
        }
        printf("\n");
        sleep(1);
    }
    return 0;
}
```

