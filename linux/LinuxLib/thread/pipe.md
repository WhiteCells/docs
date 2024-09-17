```c
/*
    // 创建匿名管道用于具有关系的进程间的通信
    #include <unistd.h>

    On Alpha, IA-64, MIPS, SuperH, and SPARC/SPARC64; see NOTES
    struct fd_pair {
        long fd[2];
    };
    struct fd_pair pipe();

    On all other architectures
    int pipe(int pipefd[2]);
        argument:
            - pipefd[2]: 传出参数，
                - pipefd[0]: 对应管道的读端
                - pipefd[1]: 对应管道的写端
        return:
            - -1: failed, set errno
            -  0: success

 */

#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <stdio.h>
#include <string.h>

/*
    子进程发送数据给父进程
    父进程读取到子进程发送的数据，然后输出
    父进程发送数据给子进程
    子进程读取到父进程发送的数据，然后输出

    管道默认是阻塞的，如果管道中没有数据，read 阻塞，如果管道满了，write 阻塞
 */

/*
    close(pipe_fd); // 关闭管道一端
 */
int main() {
    int c_p_pipe_fd[2] = { 0 }; // 子进程 => 父进程 管道
    int p_c_pipe_fd[2] = { 0 }; // 父进程 => 子进程 管道
    int c_p_ret = pipe(c_p_pipe_fd);
    int p_c_ret = pipe(p_c_pipe_fd);

    if (-1 == c_p_ret || -1 == p_c_ret) {
        perror("pipe");
        return -1;
    }

    pid_t s_pid = fork();

    if (0 == s_pid) {
        char buf[1024] = { 0 };
        while (1) {
            printf("enter child process write message:");

            fgets(buf, sizeof(buf), stdin);
            int w_len = write(c_p_pipe_fd[1], buf, strlen(buf)) - 1;  // '\0'
            buf[strlen(buf)] = '\0';
            printf("child process [%d] write date: %swrite message len: %d\n", getpid(), buf, w_len);
            sleep(1);

            long r_len = read(p_c_pipe_fd[0], buf, sizeof(buf)) - 1; // '\0'
            printf("child process [%d] read  date: %s\nread message len: %ld\n", getpid(), buf, r_len);
            sleep(1);
        }
    }
    else if (0 < s_pid) {
        char buf[1024] = { 0 };
        while (1) {
            long r_len = read(c_p_pipe_fd[0], buf, sizeof(buf)) - 1; // '\0'
            printf("parent process [%d] read  date: %s\nread message len: %ld\n", getpid(), buf, r_len);
            sleep(1);

            printf("enter parent process write message:");
            fgets(buf, sizeof(buf), stdin);
            int w_len = write(p_c_pipe_fd[1], buf, strlen(buf)) - 1; // '\0'
            buf[strlen(buf)] = '\0';
            printf("parent process [%d] write date: %swrite message len: %d\n", getpid(), buf, w_len);
            sleep(1);
        }
    }
    return 0;
}

```

