```c
/*
    // 设置定时器, 可以替代 alarm, 精度比 alarm 高
    // 实现周期性的定时, 非阻塞
    #include <sys/time.h>

    int setitimer(int which, const struct itimerval *new_value,
                 struct itimerval *old_value);
        argument:
            - which: 定时器以什么时间计时
                - ITIMER_REAL: 真实时间, 时间达到会发送 SIGALRM 信号给当前进程, 并终止进程
                - ITIMER_VIRTUAL: 用户时间, 时间到达发送 SIGVTALRM 信号给当前进程, 并终止进程
                - ITIMER_PROF: 以该进程在用户态和内核态消耗的时间计时, 时间到达发送 SIGPROF 信号给当前进程, 并终止进程
            - new_value: 设置定时器属性
            - old_value: 记录上一次的定时时间参数, 一般不使用指定 NULL

        return:
            - 0: success
            - -1: error, set errno


    ps:
        struct itimerval {              // 定时器结构体
            struct timeval it_interval; // Interval for periodic timer
            struct timeval it_value;    // Time until next expiration
        };

        struct timeval {                // 时间结构体
            time_t      tv_sec;         // seconds
            suseconds_t tv_usec;        // microseconds
        };
 */
```

```c
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

    struct itimerval new_value;

    // 设置间隔时间, 每隔 2 秒发送信号
    new_value.it_interval.tv_sec = 2;
    new_value.it_interval.tv_usec = 0;

    // 设置延迟的时间, 3 秒后开始第一次定时
    new_value.it_value.tv_sec = 3;
    new_value.it_value.tv_usec = 0;
    int ret = setitimer(ITIMER_REAL, &new_value, NULL);

    if (-1 == ret) {
        perror("setitimer");
        exit(0);
    }
    
    getchar();
    return 0;
}
```

