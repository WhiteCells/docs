### unique_lock

定义于 `<mutex>`。

`unique_lock` 和 `lock_guard` 相似，构造时默认加锁，析构时默认解锁，但 `unique_ptr` 可以手动解锁和加锁，所以可以用于控制加锁的范围（控制锁的精细程度）。也支持和条件变量使用。

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

`unique_lock` 支持领养锁。

```cpp
std::mutex mtx;

void adopt_lock() {
    // mtx.lock();
    std::unique_lock<std::mutex> lock(mtx, std::adopt_lock);
    std::cout << lock.owns_lock() << std::endl; // 1
}
```

无论互斥量是否加锁，输出都为 `1`。

当 `std::mutex` 被 `std::unique_lock` 管理时，加锁和解锁的操作（所有权）就由 `std::unique_lock` 管理，不能再调用 `std::mutex` 的加锁和解锁。

`std::mutex` 不支持移动和拷贝，但 `std::unique_lock` 支持移动。

### 共享锁

定义于 `<shared_mutex>`。

共享锁需要使用 `std::shared_mutex`（C++17），或者 `std::shared_timed_mutex`（C++14），他们都用于实现多线程并发访问共享数据的互斥锁，存在异同：

- 都提供 `lock()`、`try_lock()`、`try_lock_for()` 和 `try_lock_until()` 用于获取互斥锁。
- 都提供 `try_lock_shared()` 和 `lock_shared()` 用于获取共享锁，但 `shared_timed_mutex` 具有超时机制。

使用 `std::shared_lock` 构建共享锁，使用 `std::lock_guard` 构建独占锁。



### 递归锁

不建议使用，因从设计上避免使用，将模块拆分，然后分块加锁。



