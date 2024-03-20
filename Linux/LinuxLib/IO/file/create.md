```c
/*
    // 创建一个新文件
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>

    int open(const char *pathname, int flags, mode_t mode); // 可变参数实现
        argument:
            - pathname: 创建的文件的路径
            - flags: 对文件的操作权限设置及其他设置
                - must include
                    - O_RDONLY
                    - O_WRONLY
                    - O_RDWR
                - optional
                    - O_CREAT 文件不存在则创建新文件
                    // ...
            - mode: 八进制的数, 表示用户对创建出的新文件的操作权限, 最终权限 mode & ~umask
                umask 八进制数, 不同的用户 umask 是不一样的, 用户面具, 普通用户 0002, root 用户 0022, 这个值是可以修改的
                0777 & ~0002
                0777 &  0775
                111111111 & 111111101
                0775
                // umask 抹去一部分权限，让创建文件的权限更加合理
        return: 文件描述符, 调用失败返回 -1
    // 补充
    flags 为 int 占 4 byte，32 bit
    flags 32 bit，每一位就是一个标志位，代表一种情况。
    | 按位与 就表示两者状态都要
       O_RDWR  02     0b00000010
    |  O_CREAT 0100   0b01000000
                    --------------
                      0b01000010

 */
```

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    int fd = open("word.txt", O_RDWR | O_CREAT, 0777); // 给权限是 0777 实际只能是当前 mode & ~umask
    if (-1 == fd) {
        perror("open");
        return -1;
    }
    close(fd);
    return 0;
}

```

