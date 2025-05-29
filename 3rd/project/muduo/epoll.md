### select 和 poll 的缺点

select 的缺点：

- 单个线程能监视的文件描述符的数量存在最大限制，Linux 内核头文件中有宏定义： `#define __FD_SETSIZE 1024`，所以默认最大监视 1024 个文件描述符，虽然可以修改，但是 select 采用轮询的方式扫描文件描述符，文件描述符越多，性能越差。
- 内核 / 用户空间内存拷贝问题，select 需要复制大量的句柄数据。
- select 返回的是含有整个句柄的数组，应用程序需要遍历整个数组才能知道哪些句柄发生事件。
- select 的触发方式是水平触发，应用程序如果没有完成对一个已经就绪的文件描述符进行 IO 操作，那之后每次 select 调用都会将这些文件描述符通知进程。

poll 使用链表保存文件描述符，因此没有监视文件描述符数量的限制，但其余的缺点都存在。

### epoll 原理及优势

epoll 没有 select 和 poll 的缺点。

epoll 通过在 Linux 内核中申请一个简易的文件系统（B+ 树），将 select / poll 调用分为以下 3 个部分：

1）调用 epoll_create() 建立一个 epoll 对象（在 epoll 文件系统中为这个句柄对象分配资源）

2）调用 epoll_ctl 向 epoll 对象中添加连接的套接字

3）调用 epoll_wait 收集发生的事件的 fd 资源

```cpp
// epoll_create 在内核创建的 eventpoll 结构
struct eventpoll {
    //
    struct re_root rbr;
    struct list_head relist;
    //
};
```

只需在进程启动时建立一个 epoll 对象，然后在需要的时候向 epoll 对象中添加或者删除事件。同时，epoll_wait 的效率也非常高，调用 epoll_wait 时，并不向操作系统复制全部连接的句柄数据，内核也不需要去遍历全部的连接。

### LT 模式

内核数据没被读完，就会一直上报数据

### ET 模式

内核数据只上报一次

### muduo 采用 LT 模式

- 不会丢失数据或消息
- 低延迟处理
- 跨平台处理





















