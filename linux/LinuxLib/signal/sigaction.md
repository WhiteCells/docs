```c
/*
    // 检查或改变信号的处理
    #include <signal.h>

    int sigaction(int signum, const struct sigaction *act,
                    struct sigaction *oldact);
        argument:
            - signum: 需要捕捉的信号 (宏值 / 编号) (IGKILL 和 SIGSTOP 这两个信号不能被捕捉和忽略)
            - act: 捕捉到信号之后的处理动作 
            - oldact: 上一次对信号捕捉相关函数的设置

        return:
            - 0: success
            - -1: error, set errno


    ps:
    struct sigaction {
        // 函数指针, 指向的函数就是信号捕捉之后的处理函数
        void     (*sa_handler)(int);
        // 
        void     (*sa_sigaction)(int, siginfo_t *, void *);
        // 临时阻塞信号集, 在信号捕捉函数执行过程中, 临时阻塞
        sigset_t   sa_mask;
        // 使用哪一个信号处理对捕捉到的信号处理
        // 0, 表示使用 sa_handker 
        // SA_SIGINFO 表示使用 sa_sigaction
        int        sa_flags;
        // 已被废弃, 指定 NULL
        void     (*sa_restorer)(void);
    };
 */
```

```c
#include <signal.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

void handle(int num) {
    printf("caught signal number: %d\n", num);
}

int main() {
    struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = handle;
    sigemptyset(&act.sa_mask); // 清空临时阻塞信号集

    int ret = sigaction(SIGALRM, &act, NULL);
    if (-1 == ret) {
        perror("sigactiom");
        exit(0);
    }

    struct itimerval new_time;
    new_time.it_interval.tv_sec = 2;
    new_time.it_interval.tv_usec = 0;
    new_time.it_value.tv_sec = 5;
    new_time.it_value.tv_usec = 0;

    ret = setitimer(ITIMER_REAL, &new_time, NULL);
    if (-1 == ret) {
        perror("settimer");
        exit(0);
    }
    while (1) {}
    return 0;
}
```

