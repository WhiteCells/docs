```c
/*
    // 设置信号集中的某一个信号对应的标志位为 1, 表示阻塞这个信号
    #include <signal.h>

    int sigaddset(sigset_t *set, int signum);
        argument:
            - set: 传出参数, 需要操作的信号集
            - signum: 信号宏值或编号

        return:
            - 0: success
            - -1: error, set errno
 */

```

