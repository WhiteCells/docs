```c
/*
    // 修改文件权限
    #include <sys/stat.h>

    int chmod(const char *pathname, mode_t mode);
        argument:
            - pathname: 文件路径
            - mode: 可以指定一个 8 进制的数
                S_ISUID  (04000)  set-user-ID (set process effective user ID on execve(2))
                S_ISGID  (02000)  set-group-ID  (set  process effective group ID on execve(2); mandatory locking, as described
                         in fcntl(2); take a new file's group from parent directory, as  described  in  chown(2)  and
                         mkdir(2))
                S_ISVTX  (01000)  sticky bit (restricted deletion flag, as described in unlink(2))
                S_IRUSR  (00400)  read by           owner
                S_IWUSR  (00200)  write by          owner
                S_IXUSR  (00100)  execute/search by owner
                S_IRGRP  (00040)  read by           group
                S_IWGRP  (00020)  write by          group
                S_IXGRP  (00010)  execute/search by group
                S_IROTH  (00004)  read by           others
                S_IWOTH  (00002)  write by          others
                S_IXOTH  (00001)  execute/search by others
        return:
            -  0: success
            - -1: error
            
    int fchmod(int fd, mode_t mode);
 */
```

```c
#include <sys/stat.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* 获取文件权限 */
void GetFilePermission(struct stat file_stat);

/* perror 返回值判断 */
void DetermineRetOfPerror(int ret, char* str);

/* 8 进制转 10 进制 */
void OctalToDecimal(unsigned* perm);

/* main argc 判断 */
void DetermineMainArgc(int argc, char* argv[]);

/*
./program file
 */
int main(int argc, char* argv[]) {
    /* 参数判断 */
    DetermineMainArgc(argc, argv);

    /* 获取状态文件信息 */
    struct stat file_stat;

    int ret1 = stat(argv[1], &file_stat);
    DetermineRetOfPerror(ret1, "stat");
    GetFilePermission(file_stat);

    /* 转换输入 */
    printf("enter the permissions you want to modify: ");
    unsigned perm = 0;
    scanf("%u", &perm);
    OctalToDecimal(&perm);

    /* 修改权限 */
    int ret2 = chmod(argv[1], perm);
    DetermineRetOfPerror(ret2, "chmod");

    /* 获取最新的文件状态信息 */
    int ret3 = stat(argv[1], &file_stat);
    DetermineRetOfPerror(ret3, "stat");
    GetFilePermission(file_stat);

    return 0;
}

void GetFilePermission(struct stat file_stat) {
    printf("current permission: ");
    printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
    printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
    printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
    printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");
}

void DetermineRetOfPerror(int ret, char* str) {
    if (-1 == ret) {
        perror(str);
        exit(-1);
    }
}

void OctalToDecimal(unsigned* perm) {
    unsigned tmp = *perm, i = 0;
    *perm = 0;
    while (tmp) {
        *perm += tmp % 10 * pow(8, i++);
        tmp /= 10;
    }
}

void DetermineMainArgc(int argc, char* argv[]) {
    if (2 != argc) {
        printf("paramenter error: ");
        if (2 > argc) {
            printf("too few paramenter");
        }
        else {
            printf("too many paraments:");
            for (int i = 2; i < argc; ++i) {
                printf(" %s", argv[i]);
            }
        }
        printf("\nplase use following format:\n%s filename\n", argv[0]);
        exit(-1);
    }
}
```

