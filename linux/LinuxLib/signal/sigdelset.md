```c
/*
    // 设置信号集中的某个信号对应的标位位为 0, 表示不阻塞这个信号
    #include <signal.h>

    int sigdelset(sigset_t *set, int signum);
        argument:
            - set: 传出参数, 需要操作的信号集
            - signum: 需要设置阻塞的信号编号

        return:
            - 0: success
            - -1: error, set errno
 */
```

