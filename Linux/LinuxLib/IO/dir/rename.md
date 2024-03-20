```c
/*
    // 重命名目录
    #include <stdio.h>

    int rename(const char *oldpath, const char *newpath);
        argument:
            - oldpath:
            - newpath:
        return:
            -  0: success
            - -1: error, set errno
 */
```

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    system("ls -l");
    int ret = rename("test-dir", "test2-dir");
    if (-1 == ret) {
        perror("rename");
        return -1;
    }
    printf("successfully renamed folder\n");
    system("ls -l");
    return 0;
}
```

