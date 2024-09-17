```c
/*
    // 用于获取文件的状态信息
    // Linux 中可以通过 stat file 查看 file 相关信息
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>

    int stat(const char *pathname, struct stat *statbuf);
        argument:
            - pathname: 操作文件路径
            - statbuf: 结构体变量，是一个传出参数，保存获取到的文件的信息
        return:
            - success: On success, 0 is returned
            - error: On error, -1 is returned, and errno is set appropriately


    // struct stat
    struct stat {
            dev_t     st_dev;           // 文件的设备编号                 ID of device containing file
            ino_t     st_ino;           // 文件的 inode 号                Inode number
            mode_t    st_mode;          // 文件的类型和存储的权限          File type and mode
            nlink_t   st_nlink;         // 连到该文件的硬链接数目          Number of hard links
            uid_t     st_uid;           // 用户 ID                        User ID of owner
            gid_t     st_gid;           // 组 ID                          Group ID of owner
            dev_t     st_rdev;          // 设备文件的设备编号              Device ID (if special file)
            off_t     st_size;          // 文件字节数(文件大小)            Total size, in bytes
            blksize_t st_blksize;       // 块大小                         Block size for filesystem I/O
            blkcnt_t  st_blocks;        // 块数                           Number of 512B blocks allocated
            struct timespec st_atim;    // 最后一次访问时间(time_t)        Time of last access
            struct timespec st_mtim;    // 最后一次修改时间(time_t)        Time of last modification
            struct timespec st_ctim;    // 最后一次(属性)改变时间(time_t)  Time of last status change
    };
 */
```

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    struct stat file_stat;

    int ret = stat("../word2.txt", &file_stat);
    
    if (-1 == ret) {
        perror("stat");
        return -1;
    }

    printf("word2.txt size: %ld bytes\n", file_stat.st_size); // 返回符号链接指向的文件大小
    
    return 0;
}
```

