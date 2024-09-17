```c
/*
    // 创建进程
    #include <sys/types.h>
    #include <unistd.h>

    pid_t fork(void);
        return: 返回当前进程创建的子进程 ID
                返回两次，一次在父进程中一次在子进程中
                在父进程中返回创建的子进程的 ID，ID > 0
                在子进程中返回 0 
                可以通过 fork 返回值区分父进程还是子进程
                在父进程中返回 -1 表示创建子进程失败（进程数达到系统上限），设置 errno
                On  success, the PID of the child process is returned in the parent, 
                and 0 is returned in the child.  On failure, -1 is returned in the parent, no child process is created, 
                and errno is set appropriately.
 */
```

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    int s_pid = fork();

    if (0 == s_pid) { /* 父进程中返回创建的子进程的 ID */
        for (int i = 0; i < 10 && printf("- child process pid: %d\n", getpid()); ++i) {
            sleep(1);
        }
    } else if (0 < s_pid) { /* 在子进程中返回 0 */
        for (int i = 0; i < 10 && printf("= parent process pid: %d\n", getpid()); ++i) {
            sleep(1);
        }
    } else if (-1 == s_pid) { /* 在父进程中返回 -1 表示创建子进程失败（进程数达到系统上限），设置 errno */
        perror("fork");
    }
    
    return 0;
}
```

