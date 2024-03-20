```c
/*
    #include <sys/types.h>
    #include <unistd.h>

    pid_t getpid(void);
    pid_t getppid(void);
 */
```

```c
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t cp_pid  = getpid();         // 当前进程 ID
    pid_t cpp_pid = getppid();        // 当前进程父进程 ID
    pid_t cp_pid2 = getpgid(0);       // 传入 0 返回当前进程 ID
    pid_t p_gpid  = getpgid(cp_pid);  // 传入进程的进程组 ID
    printf("cp_pid:  %d\ncpp_pid: %d\ncp_pid2: %d\np_gpid:  %d\n",
           cp_pid, cpp_pid, cp_pid2, p_gpid);
    while (1);
    return 0;
}
```

