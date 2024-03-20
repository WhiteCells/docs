```c
/*
    // 判断某个信号是否阻塞, 判断某个信号是否在指定信号集内
    #include <signal.h>

    int sigismember(const sigset_t *set, int signum);
        argument:
            - set: 需要操作的信号集
            - signum: 需要判断的信号

        return:
            - 1: signum 信号是 set 信号集成员, signum 信号是阻塞  
            - 0: signum 信号不是 set 信号集成员, signum 信号不阻塞
            - -1: error, set errno
 */
```

