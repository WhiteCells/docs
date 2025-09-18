```c
/*
    // 设置定时器, 函数调用开始倒计时
    // 当倒计时为 0 时, 函数会给当前进程发送信号: SIGALRM 
    // SIGALRM 信号默认终止当前进程, 每一个进程有且只有一个唯一的定时器
    // 函数默认不阻塞
    // 每一次调用返回上一次设置的定时器所剩余的秒, 第一次调用返回 0
    #include <unistd.h>

    unsigned int alarm(unsigned int seconds);
        argument:
            - seconds:
                - 0: 定时器取消, 定时器不进行倒计时, 不发送信号, 可以用来取消一个定时器
                - > 0: 安排在几秒内将 SIGALRM 信号传送到调用进程

        return:
            - > 0: 返回任何先前计划的定时器交付之前剩余的秒数
            - 0: 之前没有安排定时器
 */
```

```c
#include <unistd.h>
#include <stdio.h>

int main() {
    int sec = alarm(10); // 第一次调用返回 0
    printf("%d\n", sec);

    sleep(2);

    sec = alarm(3); // 返回上一次 alarm 剩余的秒
    printf("%d\n", sec);

    while (1) {}
    return 0;
}
```
