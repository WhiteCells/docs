```c
/*
    // 捕捉信号, 可以设置信号的行为
    // ANSI C 标准, 不同的 UNIX 有区别
    // 建议使用 sigaction
    #include <signal.h>

    typedef void (*sighandler_t)(int); // int 为捕捉到的信号的值

    sighandler_t signal(int signum, sighandler_t handler);
        argument:
            - signum: 捕捉的信号 (IGKILL 和 SIGSTOP 这两个信号不能被捕捉和忽略)
            - handler: 捕捉到信号时的处理行为
                - SIG_IGN: 忽略信号
                - SIG_DFL: 使用信号默认行为
                - 回调函数: 函数处理信号行为 (内核调用)

        return:
            - 成功返回上一次注册的信号处理函数的地址, 第一次调用返回 NULL
            - 失败返回 SIG_ERR, 设置 errno

    ps: The signals SIGKILL and SIGSTOP cannot be caught or ignored.
        SIGKILL 和 SIGSTOP 这两个信号不能被捕捉和忽略
 */
```

```c
#include <signal.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

void handle(int num) {
    printf("caught signal number: %d\n", num);
}

int main() {

    // 发送信号之前, 注册信号捕捉
    // signal(SIGALRM, SIG_IGN);
    // signal(SIGALRM, SIG_DFL);
    
    if (SIG_ERR == signal(SIGALRM, handle)) {
        perror("signal");
        exit(0);
    }
    
    struct itimerval new_value;

    // 设置定时器时间
    new_value.it_interval.tv_sec = 1;
    new_value.it_interval.tv_usec = 0;

    // 设置设置定时器延迟启动时间
    new_value.it_value.tv_sec = 3;
    new_value.it_value.tv_usec = 0;

    int ret = setitimer(ITIMER_REAL, &new_value, NULL);
    printf("setitimer start\n");
    if (-1 == ret) {
        exit(0);
    }

    getchar();
    return 0;
}
```