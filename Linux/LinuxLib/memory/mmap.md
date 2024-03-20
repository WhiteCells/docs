```c
/*
    // 文件从磁盘映射到内存
    #include <sys/mman.h>

    void *mmap(void *addr, size_t length, int prot, int flags,
              int fd, off_t offset);
        argument:
            - addr: 映射的内存区地址
                - NULL: 由内核自动分配
                - 有效地址:
            - length: 映射的文件长度, 长度为 0 函数返回 NULL, 长度没有到分页大小默认为一个分页大小
                - 未指定: mmap 函数自动计算文件的大小
                - 0: mmap 函数返回 NULL
                - 文件大小不能被分页大小整除，那么余下的部分将被忽略，不会被映射到内存中
            - prot: 映射区内存操作权限
                - PROT_READ: 读权限 (操作映射区必须要读权限)
                - PROT_WRITE: 写权限
                - PROT_EXEC: 可执行权限
                - PROT_NONE: 没有权限
            - flags: 标志位
                - MAP_SHARED: 映射内存区域可被多个进程共享 (默认 flags 参数)
                - MAP_PRIVATE: 不同步, 内存映射区的数据改变了,
                               原来文件不会修改, 会重新创建一个新文件 (copy on write)
                - MAP_ANONYMOUS: 与上面参数按位与的形式添加，映射不需要文件，fd 参数被忽略，offset 必须为 0，since kernel 2.4
            - fd: 文件描述符, 表示要映射的文件 (文件大小不能为 0, open 权限不能和 prot 冲突, open 权限要大于等于 prot 权限)
            - offset: 文件偏移量, 表示从文件哪个位置开始映射, 必须是 4k 的整数倍才能偏移成功
        return:
            - MAP_FAILED: ((void*) -1) 映射失败, set error
            - void*: 映射的内存地址首地址
 */
```

```c
#include <sys/types.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

/*
使用内存映射完成进程间通信

关系进程
    在没有子进程时，通过唯一的父进程，先创建内存映射区
    有了内存映射区，创建子进程
    父子进程共享创建的内存映射区

无关系进程
    准备一个大小非 0 的磁盘文件
    a 进程通过磁盘文件创建内存映射区，得到一个操作这块内存的指针
    b 进程通过磁盘文件创建内存映射区，得到一个操作这块内存的指针
 */

int main() {
    // 以读写权限打开文件
    int fd = open("ft.txt", O_RDWR);

    // 获取文件大小
    int fd_sz = lseek(fd, 0, SEEK_END);

    // 文件大小为空需要更改文件大小
    if (0 == fd_sz) {
        int ret = truncate("ft.txt", 1);
        if (-1 == ret) {
            perror("truncate");
            close(fd);
            exit(0);
        }
    }

    fd_sz = lseek(fd, 0, SEEK_END);

    // 磁盘文件映射到内存区, 返回其在内存映射区地址的首地址
    void *ptr = mmap(NULL, fd_sz, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);

    // 检查是否映射成功
    if (MAP_FAILED == ptr) {
        perror("mmap");
        close(fd);
        exit(0);
    }

    // 创建子进程
    pid_t s_pid = fork();

    if (0 == s_pid) {
        char buf[128] = { 0 };
        printf("write data: ");
        fgets(buf, sizeof(buf), stdin);
        strcpy((char *)ptr, buf);
        // strcpy((char *)ptr, "i am parent process");
    } else if (0 < s_pid) {
        wait(NULL);
        char buf[64] = { 0 };
        strcpy(buf, (char *)ptr);
        printf("read data: %s\n", buf);
    } else if (-1 == s_pid) {
        perror("fork");
        close(fd);
        exit(0);
    }

    // 关闭内存映射区地址
    munmap(ptr, fd_sz);

    close(fd);
    return 0;
}
```

