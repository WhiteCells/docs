### 基本概念

CPU 中执行的是线程，线程是程序的最小执行单元。

每个进程的所有线程共享该进程的公共资源，如虚拟地址空间、全局变量等。每个线程可以拥有自己的私有资源，如堆栈、在堆栈中定义的静态变量和动态变量、CPU 寄存器的状态等。

线程在进程环境中创建，并会在进程内部销毁，当进程退出时，该进程所产生的所有线程都会被强制退出并清除。

### 进程的状态

1. 就绪态：线程能够运行的条件以满足，在等待处理器的调度。
2. 运行态：线程在处理器中运行。
3. 阻塞态：等待处理器之外的其他条件（如 I/O 操作、互斥锁的释放、条件变量的改变等）而无法运行。
4. 终止态：线程函数运行结束或被其他线程取消。处于终止态的线程所占用的资源未被回收。

### 线程函数

```cpp
void *ThreadProc(void *arg);
```

### 线程标识

**句柄**标识线程对象，线程本身用 **ID** 标识，在创建线程时，系统会为线程分配唯一的 **ID**，该 **ID** 从线程创建开始存在，伴随线程的结束才消失（不必显式清除）。

#### pthread_self

函数 `pthread_self` 用于获取线程 ID，这个函数不会失败。

```c
#include <pthread.h>

// 获取当前线程 ID
pthread_t pthread_self(void);
    // return:
        - 返回线程 ID，这个函数一定成功
```

### 创建线程

#### pthread_create

```c
#include <pthread.h>

// 创建线程
int pthread_create(pthread_t *restrict thread,
                    const pthread_attr_t *restrict attr,
                    void *(*start_routine)(void *),
                    void *restrict arg);
    // parameter:
        - thread: 传出参数，创建线程成功后返回的线程 ID
        - attr: 线程属性联合体，为 NULL 则使用默认属性
        - start_routine: 线程函数地址
        - arg: 线程函数的参数

    // return:
        - 成功返回 0，失败返回错误码，并且 *thread 内容未定义
```

### 等待线程

#### pthread_join

函数 `pthread_join` 用于等待子线程结束，即子线程执行完后，`pthread_join` 才返回，因此 `pthread_join` 是一个阻塞函数，该函数会让主线程挂起（即休眠，让出 CPU），直到所等待的线程都退出，然后释放等待的线程所占用的资源。等待的线程退出后，主线程会接受到系统的信号，从休眠中恢复。

```c
#include <pthread.h>

// 等待指定线程结束
int pthread_join(pthread_t thread, void **retval);
    // parameter:
        - thread: 等待线程的 ID
        - retval: 通常设置为 NULL，
                  如果非空则 pthread_join 复制一份线程退出值到一个内存区域，
                  并让 *__thread_return 指向该内存区域

    // return:
        - 成功返回 0，失败返回错误码
```

### 分离线程

#### pthread_detach

函数 `pthread_detach` 用于将一个线程设置为可分离线程。

```c
#include <pthread.h>

// 设置线程分离状态为可分离
int pthread_detach(pthread_t thread);
    // parameter:
        - thread: 设置为可分离的线程的线程 ID

    // return:
        - 成功返回 0，失败返回错误码
```

### 线程的属性

POSIX 标准规定线程具有：分离状态（Detached State）、调度策略和参数（Scheduling Policy and Parameters）、作用域（Scope）、栈尺寸（Stack Size）、栈地址（Stack Address）、优先级（Priority）等属性。

Linux 为线程属性定义一个**联合体** `pthread_attr_t`。

```c
union pthread_attr_t
{
  char __size[__SIZEOF_PTHREAD_ATTR_T];
  long int __align;
};
```

#### pthread_getattr_np

函数 `pthread_getattr_np` 用于获取线程属性联合体，使用该函数之前需要在 `pthread.h` 前定义 `_GNU_SOURCE` 宏，当不需要属性联合体时应使用 `pthread_attr_destroy` 进行销毁。

```c
#define _GNU_SOURCE
#include <pthread.h>

// 获取线程属性
int pthread_getattr_np(pthread_t thread, pthread_attr_t *attr);
    // parameter:
        - pthread: 线程 ID
        - attr: 传出参数，返回线程属性联合体

    // return:
        - 成功返回 0，失败返回错误码

    // note:
        - 使用该函数前需要在 pthread.h 前定义宏 _GNU_SOURCE
```

#### pthread_attr_init

函数 `pthread_attr_init` 用于初始化线程属性联合体。

```c
#include <pthread.h>

// 初始化线程属性联合体
int pthread_attr_init(pthread_attr_t *attr);
    // parameter:
        - attr: 传出参数，需要初始化的线程属性联合体

    // return:
        - 成功返回 0，失败返回错误码
```

#### pthread_attr_destroy

函数 `pthread_attr_destroy` 用于销毁 `pthread_getattr_np` 获取的线程属性联合体。

```c
#include <pthread.h>

// 销毁线程属性联合体
int pthread_attr_destroy(pthread_attr_t *attr);
    // parameter:
        - attr: 传出参数，需要销毁的线程属性联合体

    // return:
        - 成功返回 0，失败返回错误码
```

##### 分离状态

POSIX 线程的分离状态决定线程终止方式。

线程分离状态：**可分离状态**和**非可分离状态**（**可连接**，joinable），前者用宏 `PTHREAD_CREATE_DETACHED` 表示，后者用宏 `PTHREAD_CREATE_JOINABLE` 表示（定义于 `pthread.h` 文件）。

默认分离状态为可连接，可连接的线程可以被其他线程收回资源和取消，不会主动释放资源（比如栈空间），必须由其他线程来回收其资源，因此需要在其他线程使用 `pthread_join` 函数，**当 `pthread_join` 函数返回后，所等待的线程的资源才被释放**，如果是线程自己返回结束或调用 `pthread_exit` 结束都不会释放线程所占用的资源（堆栈和线程描述符）。

**一个线程不能被多个线程等待**，否则第一个收到信号的线程成功返回，其余调用 `pthread_join` 的线程将得到错误代码 `ESRCH`。

可分离的线程在运行结束时，其资源立刻被系统回收，可以在线程创建时设置为可分离状态或调用 `pthread_detach` 函数来设置可分离线程。

对于可连接线程，可以使用 `pthread_join` 函数等待子线程执行结束，而对于分离线程，可以在主线程调用函数 `pthread_exit` 终止主线程，进程创建的资源会由主线程创建的其他线程保持打开状态，直到其他线程都终止，在非主线程中调用函数 `pthread_exit` 只会退出当前子线程。

###### pthread_attr_setdetachstate

函数 `pthread_attr_setdetachstate` 用来设置线程属性联合体的分离状态属性，可设置的宏为 `PTHREAD_CREATE_DETACHED` 或 `PTHREAD_CREATE_JOINABLE`。

```c
#include <pthread.h>

// 设置线程属性联合体的分离状态属性
int pthread_attr_setdetachstate(pthread_attr_t *attr, 
                                int detachstate);
    // parameter:
        - attr: 需要设置的线程属性联合体变量
        - detachstate: 传入参数，分离状态值

    // return:
        - 成功返回 0，失败返回错误码
    
    // note:
        - 分离状态宏：
            PTHREAD_CREATE_DETACHED
            PTHREAD_CREATE_JOINABLE
```

###### pthread_attr_getdetachstate

函数 `pthread_attr_getdetachstate` 用来获取线程属性联合体的分离状态属性。

```c
#include <pthread.h>

// 获取线程分离状态值
int pthread_attr_getdetachstate(const pthread_attr_t *attr,
                                int *detachstate);
    // parameter:
        - attr: 需要获取分离状态的线程属性联合体
        - detachstate: 传出参数，线程属性联合体的分离状态值

    // return:
        - 成功返回 0，失败返回错误码
```

##### 栈尺寸

线程的局部变量、函数参数、返回地址等都放在栈空间，在线程函数中开设局部变量（尤其是数组），需要注意不要超过默认栈尺寸。宏 `PTHREAD_STACK_MIN` 定义默认栈尺寸。

###### pthread_attr_setstacksize

函数 `pthread_attr_setstacksize` 用于设置线程栈尺寸。

```c
#include <pthread.h>

// 设置线程栈尺寸
int pthread_attr_setstacksize(pthread_attr_t *attr, 
                              size_t stacksize);
    // parameter:
        - attr: 传入参数，需要设置的线程属性联合体
        - stacksize: 设置的栈尺寸（字节）

    // return:
        - 成功返回 0，失败返回错误码
```

###### pthread_attr_getstacksize

函数 `pthread_attr_getstacksize` 用于获取线程栈尺寸。

```c
#include <pthread.h>

// 获取线程栈尺寸
int pthread_attr_getstacksize(const pthread_attr_t *restrict attr,
                              size_t *restrict stacksize);
    // parameter:
        - attr: 传入参数，需要获取栈尺寸的线程属性联合体
        - stacksize: 传出参数，栈尺寸（字节）
    
    // return:
        - 成功返回 0，失败返回错误码
```

##### 调度策略

调度策略管理线程如何使用 CPU，调度策略由操作系统安排，不同的操作系统其调度策略不同。在理解线程调度之前，需要先理解**实时**与非实时（**分时**），实时（Real-time）是指操作系统对一些中断等的响应时效性非常高，非实时（Time-sharing）则相反。VxWorks 属于实时操作系统，而 Windows 和 Linux 则属于非实时操作系统，也叫分时操作系统。

Linux 虽然是非实时操作系统，但其线程也有实时和分时之分，具体的调度策略有：**SCHED_OTHER**（分时调度策略）、**SCHED_FIFO**（先来先服务调度策略，只用于实时线程）、**SCHED_RR**（实时的分时调度策略，只用于实时线程）。创建线程时可以指定调度策略，默认的调度策略为 **SCHED_OTHER**。

- SCHED_OTHER

  **分时调度策略**，轮转策略，是一种非实时调度策略，不支持优先级，系统为每个进程分配时间片。

- SCHED_FIFO

  **先来先服务调度策略**，只用于实时线程，是一种实时调度策略，支持优先级抢占，线程一旦占用 CPU 则一直运行，直到有更高优先级任务到达或自己放弃 CPU，如果有和正在运行的线程具有相同的优先级的线程，则必须等待正在执行的线程主动放弃后才可以运行该同优先级的线程。

- SCHED_RR

  **时间片轮询调度策略**，是一种实时调度策略，支持优先级抢占，CPU 为每个线程分配时间片，当线程的时间片用完，系统将重新分配时间片，并将线程置于实时线程就绪队列的尾部，保证所有具有相同优先级的线程能被公平的调度。

###### sched_get_priority_min

函数 `sched_get_priority_min` 用于获取线程调度策略优先级的最小值。

```c
#include <sched.h>

// 获取调度策略的最低优先级值
int sched_get_priority_min(int policy);
    // parameter:
        - policy: 调度策略

    // return:
        - 成功返回调度策略的最低优先级值
          失败返回 -1，并设置 errno

    // note:
        - 调度策略
            - SCHED_OTHER
            - SCHED_FIFO
            - SCHED_RR
```

###### sched_get_priority_max

函数 `sched_get_priority_max` 用于获取线程调度策略优先级的最大值。

```c
#include <sched.h>

// 获取调度策略的最高优先级值
int sched_get_priority_max(int policy);
    // parameter:
        - policy: 调度策略

    // return:
        - 成功返回调度策略的最高优先级值
          失败返回 -1，并设置 errno

    // note:
        - 调度策略
            - SCHED_OTHER
            - SCHED_FIFO
            - SCHED_RR
```

#### 结束线程

Linux 下，线程的结束通常有以下情况：

1. 在线程函数中调用 `pthread_exit`
2. 线程函数执行结束后返回
3. 线程被同一进程中的其他线程通知结束或取消
4. 线程所属的进程结束，如进程调用 `exit`

##### 主动结束

###### pthread_exit

函数 `pthread_exit` 用于结束线程。

```c
#include <pthread.h>

// 结束线程
[[noreturn]] void pthread_exit(void *retval);
    // parameter:
        - retval: 线程函数终止后通过 retval 记录返回值
                  使用 pthread_join 第二个参数接受
```

##### 被动结束

###### pthread_kill

函数 `pthread_kill` 用于给指定线程发送信号，用于线程间通信，接受线程的函数必须先用 `sigaction` 函数注册信号的处理函数。 

信号通常是大于 0 的值，当等于发送 0 时，然后判断返回值可**用于探测线程是否存活**。

向指定线程发送信号，如果指定线程不进行处理，则按信号的默认行为影响整个**进程**，如果给一个线程发送 `SIGQUIT` 信号，线程没有处理，则整个进程退出（应避免使用 `pthread_kill` 终止线程，因为这这会导致资源泄漏或数据不一致的问题）。

```c
#include <signal.h>

// 给指定线程发送信号
int pthread_kill(pthread_t thread, int sig);
    // parameter:
        - thread: 线程 ID
        - sig: 信号
    
    // return:
        - 成功返回 0，失败返回错误码，并且不发送信号
          ESRCH：线程不存在
          EINVAL：信号不合法
```

###### pthread_cancel

函数 `pthread_cancel` 用于取消指定线程执行。发送成功不代表被取消的线程会立即停止运行，只有在被取消线程下次调用系统函数和 C 库函数（如 `printf`）或者调用函数 `pthread_testcancel` （让内核检查是否需要取消当前线程）时，才会真正的结束被取消的线程。在线程执行的过程中，检查是否有未响应取消信号的地方，称为**取消点**，常见的取消点在 `printf`、`pthrad_testcancel`、`read`、`write`、`sleep` 等函数调用地方。如果被取消线程停止运行，将自动返回常量 `PTHREAD_CANCELED`（-1），可以通过 `pthread_join` 获取这个返回值。

```c
#include <pthread.h>

// 取消指定线程的执行，发送取消请求
// 发送成功不代表被取消的线程会立即停止运行
int pthread_cancel(pthread_t thread);
    // parameter:
        - thread: 线程 ID

    // return:
        - 成功返回 0，失败返回错误码
```

###### pthread_testcancel

`pthread_testcancel` 函数用于让内核检查是否需要取消当前线程。

```c
#include <pthread.h>

// 让内核检查是否需要取消当前线程
void pthread_testcancel(void);
```

##### 线程退出时的清理机会

被动结束是其他线程要求其结束，这种退出方式是不可预见的，是一种异常终止，无论是正常终止还是异常终止，都需要保证线程终止时能顺利的释放自己所占用的资源，尤其是锁资源。

线程为了访问临界资源而为其加锁，如果在访问时线程被其他线程取消，且取消成功，则该临界资源将永远处于加锁状态。

```c
void *foo(void *arg) {
    pthread_mutex_lock(&mtx);
    pthread_testcancel(); // 其他线程对该线程发送取消请求
    pthread_mutex_unlock(&mtx); // 锁未被释放
}
```

因此需要一种机制来确保线程在异常退出能释放所占资源。

###### pthread_cleanup_push

函数 `pthread_cleanup_push` 用于将函数压入清理函数**栈**，必须与 `pthread_cleanup_pop` 成对使用。

**清理函数运行的三种情况**：

1. 线程主动结束
2. `pthread_cleanup_pop` 传入参数为 0
3. 线程异常终止

```c
#include <pthread.h>

// 将函数压入清理函数栈
void pthread_cleanup_push(void (*routine)(void *), void *arg);
    // parameter:
        - routine: 清理函数的指针
        - arg: 清理函数的参数
```



###### pthraed_cleanup_pop

函数 `pthread_cleanup_pop` 将函数从清理函数栈中退出。

```c
#include <pthread.h>

// 弹出栈顶清理函数，并选择是否执行清理函数 
void pthread_cleanup_pop(int execute);
    // parameter:
        - execute: 选择弹出栈顶清理函数的同时，是否执行清理函数
                   非 0 时表示执行清理函数
```



### 线程同步















