### pthread_create

```cpp
#include <pthread.h>

int pthread_create(pthread_t *restrict thread,
                          const pthread_attr_t *restrict attr,
                          void *(*start_routine)(void *),
                          void *restrict arg);
```



```cpp
#include <pthread.h>
#include <stdio.h>

void *foo(void *arg) {
    (*((int *)arg))++;
    printf("sub thread\n");
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t pid;
    int n = 0;
    int ret = pthread_create(&pid, NULL, foo, &n);
    if (ret) {
        printf("pthread_create failed %d\n", ret);
        return -1;
    }

    printf("main thread\nn = %d\n", n);
    return 0;
}
```

`n` 的结果可能为 0 也可能为 1，这是因为主线程可能在子线程还未执行时就已结束，从而导致进程结束，需要在主线程结束之前对子线程使用 `thread_join` 进行等待，并回收子线程资源。

### pthread_join

```cpp
#include <pthread.h>

int pthread_join(pthread_t thread, void **retval);
    argument:
        - thread: 子线程标识
        - retval: 
    return: 成功返回 0，失败返回错误码
```



```cpp
#include <pthread.h>
#include <stdio.h>

void *foo(void *arg) {
    (*((int *)arg))++;
    printf("sub thread\n");
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t pid;
    int n = 0;
    int ret = pthread_create(&pid, NULL, foo, &n);
    if (ret) {
        printf("pthread_create failed: %d\n", ret);
        return -1;
    }

    pthread_join(pid, NULL);
    printf("main thread\nn = %d\n", n);
    return 0;
}
```



### pthread_getattr_np

```cpp

```





### pthread_attr_init

```cpp

```





### pthread_attr_destroy

```cpp

```



### pthread_getattr

```

```

