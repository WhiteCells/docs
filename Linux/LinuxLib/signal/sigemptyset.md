```c
/*
    // 信号集所有标志位置 0
    #include <signal.h>

    int sigemptyset(sigset_t *set);
        argument:
            - set: 传出参数, 需要操作的信号集
            
        return:
            - 0: success
            - -1: error, set errno
 */
```

```c
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void sigIsMember(sigset_t *sset, int sig) {
    int ret = sigismember(sset, sig);
    if (0 == ret) {
        printf("信号: %d 不阻塞\n", sig);
    } else if (1 == ret) {
        printf("信号: %d 阻塞\n", sig);
    } else {
        perror("sigismember");
        exit(0);
    }
}

int main() {
    sigset_t sset;

    // 信号集置 0
    sigemptyset(&sset);

    sigIsMember(&sset, SIGINT); // 信号: 2 不阻塞

    sigaddset(&sset, SIGINT);
    sigaddset(&sset, SIGQUIT);

    sigIsMember(&sset, SIGINT); // 信号: 2 阻塞
    sigIsMember(&sset, SIGQUIT); // 信号: 3 阻塞

    sigdelset(&sset, SIGQUIT);
    sigIsMember(&sset, SIGQUIT); // 信号: 3 不阻塞

    return 0;
}
```

