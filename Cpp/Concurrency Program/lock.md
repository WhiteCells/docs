### unique_lock

`unique_lock` 和 `lock_guard` 相似，定义于 `<mutex>` 头文件，构造时默认加锁，析构时默认解锁，但 `unique_ptr` 可以手动解锁和加锁，所以可以用于控制加锁的范围。也支持和条件变量使用。

```cpp
std::mutex mtx;
int data = 0;
void use_unique_lock() {
    std::unique_lock<std::mutex> lock(mtx);
    ++data;
    lock.unlock();
}
```

可以通过方法 `owns_lock()` 判断是否持有锁。

```cpp
void use_owns_lock_api() {
    std::unique_lock<std::mutex> lock(mtx);
    ++data;
    if (lock.owns_lock()) {
        std::cout << "lock.owns_lock()" << std::endl;
    }
    lock.unlock();
    if (!lock.owns_lock()) {
        std::cout << "!lock.owns_lock()" << std::endl;
    }
    lock.lock();
    if (lock.owns_lock()) {
        std::cout << "lock.owns_lock()" << std::endl;
    }
}
```

 `unique_lock` 可以延迟加锁。

```cpp
void defer_lock() {
    std::unique_lock<std::mutex> lock(mtx, std::defer_lock);
    std::cout << lock.owns_lock() << std::endl; // 0
    lock.lock(); // defer lock
    std::cout << lock.owns_lock() << std::endl; // 1
    ++data;
    lock.unlock();
    std::cout << lock.owns_lock() << std::endl; // 0
}
```

