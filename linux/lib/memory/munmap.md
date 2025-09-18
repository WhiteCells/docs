```c
/*
    // 释放映射内存
    #include <sys/mman.h>

    int munmap(void *addr, size_t length);
        argument:
            - addr: 释放的映射的内存区地址首地址
            - length: 释放的映射的内存区大小, 需和 mmap 中 length 一致

        return:
            - 0: success
            - -1: error, set errno
 */
```

