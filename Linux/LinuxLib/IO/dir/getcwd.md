```c
/*
    // 获取当前工作目录
    #include <unistd.h>

    char *getcwd(char *buf, size_t size);
        argument:
            - buf: 存储路径
            - size: buf 数组大小
        return:
            - char*: On success, these functions return a pointer to a string containing the pathname of the current working directory
            - NULL:  these  functions return NULL, and errno is set to indicate the error.  The contents of the array pointed to by buf are undefined on error.
    
    char *getwd(char *buf); // the function is dangerous and should not be used.
    char *get_current_dir_name(void);
 */
```

```c
#include <unistd.h>
#include <stdio.h>

int main() {
    char buf[1024] = { 0 };
    char* pathname = getcwd(buf, 1024);
    if (NULL == pathname) {
        perror("getcwd");
        return -1;
    }
    printf("current working directory: %s\n", pathname);
    return 0;
}
```

