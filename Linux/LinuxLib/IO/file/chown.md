```c
/*
    // 修改文件所有者和所在组
    #include <unistd.h>

    int chown(const char *pathname, uid_t owner, gid_t group);
        argument:
            - pathname: 文件路径
            - owner: 新的所有者用户 ID
            - group: 新的所在组用户 ID
        return:
            -  0: success
            - -1: error

    int fchown(int fd, uid_t owner, gid_t group);
    int lchown(const char *pathname, uid_t owner, gid_t group);
 */
```

```c
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

int main() {
    struct stat file_stat;

    int ret1 = stat("option.txt", &file_stat);
    if (-1 == ret1) {
        perror("stat");
        return -1;
    }
    printf("file uid: %u\n", file_stat.st_uid);
    printf("file gid: %u\n", file_stat.st_gid);

    int ret2 = chown("option.txt", 1000, 1000); // cat /etc/passwd
    if (-1 == ret2) {
        perror("chown");
        return -1;
    }

    printf("ownership changed successfully.\n"); // sudo ./chown
    int ret3 = stat("option.txt", &file_stat);
    if (-1 == ret3) {
        perror("stat");
        return -1;
    }
    printf("file uid: %u\n", file_stat.st_uid);
    printf("file gid: %u\n", file_stat.st_gid);

    return 0;
}

```

