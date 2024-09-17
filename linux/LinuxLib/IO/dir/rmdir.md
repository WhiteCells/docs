```c
/*
    // 删除一个空目录
    #include <unistd.h>

    int rmdir(const char *pathname);
        argument:
            - pathname: 删除目录路径
        return:
            -  0: success
            - -1: error, set errno
 */
```

```c
#include <unistd.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int ret = rmdir("test-dir");
    if (-1 == ret) {
        perror("rmdir");
        return -1;
    }
    printf("successfully removed folder\n");
    return 0;
}

```

