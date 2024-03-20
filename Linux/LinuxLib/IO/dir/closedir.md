```c
/*
    // 关闭目录
    #include <sys/types.h>
    #include <dirent.h>

    int closedir(DIR *dirp);
        argument:
            - drip: closes the directory stream associated with dirp,
                    A successful call to closedir() also closes the underlying file descriptor associated with dirp.
                    The directory stream descriptor dirp is  not available after this call
        return:
            -  0: success
            - -1: error, set errno
 */
```

