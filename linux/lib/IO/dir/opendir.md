```c
/*
    // 打开目录
    #include <sys/types.h>
    #include <dirent.h>

    DIR *opendir(const char *name);
        argument:
            - name: 绝对路径
        return:
            - NULL: error, set errno
            - DIR*: success, directory stream
    DIR *fdopendir(int fd);

    // 读取目录，第一次调用读取第一个，第二次调用向后读取一个，依此类推
    #include <dirent.h>

    struct dirent *readdir(DIR *dirp);
        argument:
            - dirp: directory stream
        return:
            - NULL: It returns NULL on reaching the end of the directory stream or if an error occurred.
            - struct dirent*:  returns a pointer to a dirent structure representing the next directory entry in the directory stream pointed to by dirp

    // 补充
    struct dirent {
               ino_t          d_ino;       // Inode number           目录进入点 inode
               off_t          d_off;       // Not an offset          目录文件开头至目录文件进入点的位移
               unsigned short d_reclen;    // Length of this record  d_name 的长度，不包含 NULL 字符
               unsigned char  d_type;      // Type of file; not supported by all filesystem types  d_name 文件类型 // DT_BLK - 块设备 DT_CHR - 字符设备 DT_DIR - 目录 DT_LNK - 软连接 DT_REG - 普通文件 Dt_SOCK - 套接字 DT_UNKNOWN - 未知
               char           d_name[256]; // Null-terminated filename                              文件名
    };
 */
```

```c
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
实现查看目录下所有的普通文件的个数
./opendir path
*/

int GetPathFileNum(const char* path) { // ?? bug
    /* 打开目录 */
    DIR* dirp = opendir(path);

    if (NULL == dirp) {
        perror("opendir");
        exit(-1);
    }

    struct dirent* entry;

    int cnt_reg_file = 0;

    /* 读打开目录下的文件 */
    while (NULL != (entry = readdir(dirp))) {
        char* dname = entry->d_name; // 路径下获取文件的名字
        // 忽略 . 和 .. 目录
        if (!strcmp(dname, ".") || !strcmp(dname, "..")) {
            continue;
        }
        // 如果当前读到的是目录就要进入目录
        if (DT_DIR == entry->d_type) {
            // 拼接新目录
            char new_path[512] = { 0 };
            sprintf(new_path, "%s/%s", path, dname);
            cnt_reg_file = GetPathFileNum(new_path); // 递归调用进入新目录
        }
        // 如果当前读到的是文件就计数
        else if (DT_REG == entry->d_type) {
            ++cnt_reg_file;
        }
    }
    /* 关闭目录 */
    closedir(dirp);
    return cnt_reg_file;
}

void GetREGFile(const char* path, int* cnt) {
    /* 打开目录 */
    DIR* dirp = opendir(path);
    if (NULL == dirp) {
        perror("opendir");
        exit(-1);
    }

    struct dirent* entry;

    while (NULL != (entry = readdir(dirp))) {
        char* dname = entry->d_name;
        // 忽略 .. . 目录
        if (!strcmp(dname, ".") || !strcmp(dname, "..")) {
            continue;
        }
        // 目录
        if (DT_DIR == entry->d_type) {
            char new_path[256] = { 0 };
            sprintf(new_path, "%s/%s", path, dname);
            GetREGFile(new_path, cnt);
        }
        // 普通文件
        else if (DT_REG == entry->d_type) {
            ++*cnt;
        }
    }
    /* 关闭目录 */
    closedir(dirp);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("parameters error:");
        if (argc < 2) {
            printf("too few parameters\n");
        }
        else {
            printf("too many parameters: ");
            for (int i = 2; i < argc; ++i) {
                printf("%s ", argv[i]);
            }
            printf("\n");
        }
        printf("plase enter the format below:\n%s path\n", argv[0]);
        return -1;
    }

    // int reg_file_num = GetPathFileNum(argv[1]);
    // printf("%d\n", reg_file_num);

    int reg_file_num = 0;
    GetREGFile(argv[1], &reg_file_num);
    printf("%d\n", reg_file_num);

//     /* 打开目录 */
//     DIR* dir = opendir(argv[1]);
//     if (NULL == dir) {
//         perror("opendir");
//         return -1;
//     }
// 
//     /* 读目录 */
//     struct dirent* entry = readdir(dir);
//     while (NULL != (entry = readdir(dir))) {
//         printf("%s\n", entry->d_name);
//     }
// 
//     /* 关闭目录 */
//     closedir(dir);
    return 0;
}
```

