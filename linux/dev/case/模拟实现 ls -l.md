```c
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

/*
int main(int argc, char const *argv[]) 是主函数 main 的标准参数列表。下面对这些参数进行逐个讲解：

    int argc：表示命令行参数的数量，即参数个数（argument count）。当程序运行时，可以在命令行中传递参数给程序，argc 就是用来记录这些参数数量的变量。注意，argc 包括程序名称本身，因此至少为 1。

    char const *argv[]：是一个字符指针数组，用于存储命令行参数的字符串（argument vector）。每个元素 argv[i]（其中 0 <= i < argc）都是一个 C 字符串，表示一个命令行参数。
        char const * 表示指向字符常量的指针，每个指针指向一个命令行参数字符串。
        argv[] 是一个数组，用于存储这些指针。

    通过数组的索引可以访问每个命令行参数的字符串。通常，argv[0] 存储程序的名称，而 argv[1]、argv[2] 等存储传递给程序的命令行参数。

例如，如果你在命令行中输入 ./program arg1 arg2 来运行程序，那么：

    argc 的值将为 3（包括程序名）。
    argv[0] 的值将为 "./program"。
    argv[1] 的值将为 "arg1"。
    argv[2] 的值将为 "arg2"。

通过使用 argc 和 argv，你可以在程序中动态地处理和利用命令行参数。
 */

/*
    套接字（Socket）：套接字是一种网络通信的接口，用于在计算机网络上进行进程间的通信。它允许不同机器上的进程通过网络传输数据。套接字可以是面向连接的（如 TCP 套接字）或无连接的（如 UDP 套接字）。

    软链接（Symbolic Link，也称为符号链接）：软链接是一个指向另一个文件或目录的特殊类型的文件。它类似于快捷方式，可以跨越不同的文件系统和目录边界。软链接以路径名的形式存在，指向实际文件或目录的位置。

    普通文件：普通文件是计算机文件系统中最常见的文件类型。它包含了文本、二进制数据等内容。在文件系统中，普通文件是存储用户数据的标准文件类型，没有特殊的属性或行为。

    块设备（Block Device）：块设备是一种用于存储和读取数据的设备，它按块大小（如磁盘扇区）进行数据的读写操作。块设备通常用于存储大量的数据，例如硬盘驱动器和闪存设备。

    目录：目录是文件系统中用于组织和存储其他文件和目录的特殊类型的文件。它可以包含零个或多个文件和子目录。目录用于分层次地组织和管理文件系统中的文件，方便用户访问和查找文件。

    字符设备（Character Device）：字符设备是一种用于输入和输出字符数据的设备。它以流的形式处理数据，一次一个字符地读取或写入。字符设备通常用于与终端、键盘、打印机等交互的设备。

    管道（Pipe）：管道是一种进程间通信的机制，允许一个进程的输出直接成为另一个进程的输入。它将一个进程的输出连接到另一个进程的输入，实现数据的传输。管道可以是匿名管道（在内存中创建）或命名管道（存在于文件系统中）。
 */

/*
模拟实现 ls -l file
-rwxr-xr-x 1 eorys eorys 12 Aug 24 08:25 ../word.txt
 */
int main(int argc, char const *argv[]) {
    /* 参数判断 */
    if (2 != argc) {
        printf("parameter error: ");
        if (2 < argc) {
            printf("too many parament, ");
            for (int i = 2; i < argc; ++i) {
                printf("%s ", argv[i]);
            }
        }
        else {
            printf("too few parameters");
        }
        printf("\nplease use the following format:\n%s filename\n", argv[0]);
        return -1;
    }

    struct stat file_stat;
    int ret = stat(argv[1], &file_stat);
    if (-1 == ret) {
        perror(argv[1]);
        return -1;
    }

    char file_mode[11] = { 0 };
    /*
    读权限（Read）：允许用户读取文件的内容和属性。对应的符号表示为r，对应的数字表示为4。
    写权限（Write）：允许用户修改文件的内容和属性。对应的符号表示为w，对应的数字表示为2。
    执行权限（Execute）：对于可执行文件，允许用户执行该文件。对于目录，允许用户进入该目录。对应的符号表示为x，对应的数字表示为1。
     */
    /* 1.文件权限 */
    // 文件类型
    switch (file_stat.st_mode & __S_IFMT) {
        case __S_IFSOCK: /* 套接字 */
            file_mode[0] = 's';
            break;
        case __S_IFLNK: /* 软连接 */
            file_mode[0] = 'l';
            break;
        case __S_IFREG: /* 普通文件 */
            file_mode[0] = '-';
            break;
        case __S_IFBLK: /* 块设备 */
            file_mode[0] = 'b';
            break;
        case __S_IFDIR: /* 目录 */
            file_mode[0] = 'd';
            break;
        case __S_IFCHR: /* 字符设备 */
            file_mode[0] = 'c';
            break;
        case __S_IFIFO: /* 管道 */
            file_mode[0] = 'p';
            break;
        default:
            break;
    }
    // User
    file_mode[1] = (file_stat.st_mode & S_IRUSR) ? 'r' : '-';
    file_mode[2] = (file_stat.st_mode & S_IWUSR) ? 'w' : '-';
    file_mode[3] = (file_stat.st_mode & S_IXUSR) ? 'x' : '-';
    // Group
    file_mode[4] = (file_stat.st_mode & S_IRGRP) ? 'r' : '-';
    file_mode[5] = (file_stat.st_mode & S_IWGRP) ? 'w' : '-';
    file_mode[6] = (file_stat.st_mode & S_IXGRP) ? 'x' : '-';
    // Others
    file_mode[7] = (file_stat.st_mode & S_IROTH) ? 'r' : '-';
    file_mode[8] = (file_stat.st_mode & S_IWOTH) ? 'w' : '-';
    file_mode[9] = (file_stat.st_mode & S_IXOTH) ? 'x' : '-';

    file_mode[10] = '\0';

    /* 2.硬链接数 */
    unsigned long file_nlink = file_stat.st_nlink;

    /* 3.所有者 */
    struct passwd* pw_user = getpwuid(file_stat.st_uid); // pwd.h
    char* file_user = pw_user->pw_name;

    /* 4.所属组 */
    struct group* pw_group = getgrgid(file_stat.st_gid); // grp.h
    char* file_group = pw_group->gr_name;

    /* 5.文件大小 */
    long file_size = file_stat.st_size;

    /* 6.最后修改时间 */
    long time_stamp = file_stat.st_mtime; // 在Unix和类Unix系统中，时间以秒数来表示，从 1970 年 1 月 1 日 00:00:00 UTC 开始计算
    char* time = ctime(&time_stamp); // (会带换行)

    char file_m_time[512] = { 0 };
    strncpy(file_m_time, time, strlen(time) - 1); // 不包含 '\n'

    /* 7.文件名 */
    const char* file_name = argv[1];

    char buf[1024] = { 0 };
    sprintf(buf, "%s %ld %s %s %ld %s %s",
            file_mode, file_nlink, file_user, file_group, file_size, file_m_time, file_name);
    printf("%s\n", buf);

    return 0;
}
```

