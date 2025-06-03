虚拟函数 "dock::ControlDockWindow::~ControlDockWindow" 的异常规范与重写 函数 "QWidget::~QWidget" 的异常规范不兼容

> 析构函数已存在

方法实现时，const 限定符需指明，static 修饰符不必指明，override 不必指明。

父类变量由父类初始化，子类能使用初始化列表方式只能初始化自己的成员变量，不能是父类的非静态成员变量。

即使析构函数被声明为纯虚函数也需要给出定义，所以析构函数不必声明为纯虚函数。

父类纯虚函数（除纯虚析构），派生类需要提供其实现，如不提供实现，则派生类会成为抽象类，无法实例化。

构造函数不能被声明为虚函数，因为在对象的创建过程中，虚拟机制还没有开始工作，也就是说，在构造函数调用期间，对象的动态类型尚未确定。

虚函数在运行时通过 vtable 实现多态行为，当你调用虚函数时，C++ 通过对象的 vtable 查找合适的函数进行定义，而 **vtable 是在构造函数执行过程中建立的**。

父类中的不存在默认构造，则子类实现默认构造时需要显式调用父类的构造：

```cpp
class Base {
public:
    Base(int value) {
        // 构造函数的实现
    }
};

class Derived : public Base {
public:
    Derived() : Base(1) { // 显式的调用父类的构造
        
    }
};
```

或者在 C++11 版本之后使用 using 关键字：

```cpp
class Base {
public:
    Base(int value) {
        // 构造函数的实现
    }
};

class Derived : public Base {
public:
    using Base::Base; // 继承基类的所有构造函数
    // 派生类可以有自己的构造函数，也可以没有
};
```

在 C++ 中接口通过纯虚基类来实现，纯虚基类不建议包含成员变量，因为这可能会导致接口的使用者需要了解更多的实现细节。

模板类的定义和实现需要放在同一个文件中，类中函数在类外实现时需要在类名作用域上指定模板参数 `ClassName<T>::foo()`。

纯虚函数存在实现就不再是虚函数，父类不是抽象类，子类也不会因为没有重写而成为抽象类。

常量对象其成员必须存在初始化值。

常量成员变量不初始化，则无法调用默认构造函数。

const 修饰的成员函数只能调用 const 成员函数。

父类指针不能调用子类特有的方法，需要进行类型转换。

使用 `CMakeLists.txt` 中 `include_directories` 可以简化 `include` 包含的路径名，但项目较大时，建议完整路径，防止名称冲突。

`dynamic_cast` 在进行动态类型转换，如果转换不安全会返回一个空指针（指针类型），或者抛出 `std::bad_cast` 异常（引用类型）。

`std::distance` 函数用于计算两个迭代器之间的元素数量：

```cpp
std::vector<int> v {1, 2, 3};
std::vector<int>::iterator it1 = v.begin();
std::cout << "it1 value: " << *it1 << std::endl;  // 1
std::vector<int>::iterator it2 = v.end() - 1;
std::cout << "it2 value: " << *it2 << std::endl; // 3
std::cout << std::distance(it1, it2) << std::endl; // 2
std::cout << std::distance(it2, it1) << std::endl; // -2
```



引用成员必须在构造对象时立即初始化：

```cpp
struct A {
    int &a_;
};

A a; // 无法引用 "A" 的默认构造函数 -- 它是已删除的函数
```

```cpp
struct A {
    A(int &v) : a_(v) {}
    int &a_;
};

int val = 1;
A a(val);
```

宏是在预处理阶段展开的，而命名空间是在编译阶段处理的。所以宏定义的作用域不受命名空间的限制。

宏定义中：

```cpp
#define LOG_DEBUG(msg_format, ...) \
    do { \
        \
    } while (0)
```

`do { } while(0)` 的作用是创建一个作用域，不是一个真正的循环，只是一种技巧，while(0) 后也是否有 `;` 取决于调用该宏时是否在结尾使用 `;`（因为宏只是做替换）。

定义命令空间不需要 `;`，使用命名空间需要 `;。

头文件 `inline` 声明的函数需要在头文件中定义，因为 `inline` 函数的定义需要在每一个使用它的源文件中都可见，以便编译器可以在调用点内联展开函数体。

**前置声明足够的情况**：当 A 作为指针或引用类型使用时，只需要前置声明，不需要包含头文件。在源文件使用时，在源文件中包含头文件。

**必须包含头文件的情况**：当 A 作为非指针、非引用类型（即值类型）使用时，必须包含头文件以获得 A 的完整定义。

> 前置声明只适用于指针和引用，因为在声明指针和引用时不需要知道其完整的大小和布局，可以直接确定类的大小。

使用 `using` 或 `typedef` 设置类型别名，该类型别名受访问限定符影响：

```cpp
class C {
    typedef long long ll1;
    using ui1 = int;
public:
    typedef long long ll2;
    using ui2 = int;
    
    void foo(ll1 val);
};

void C::foo(C::ll1 val) {}

class D : C {
    ll1 a = 1; // error
    ll2 b = 1;
    ui1 c = 1; // error
    ui2 c = 1;
};
```

`using` 和 `typedef` 定义的类型作为函数返回类型时，需要加上类作用域：

```cpp
#ifndef _TEST_H_
#define _TEST_H_

class A {
    using ll1 = long long;
    typedef long long ll2;
    ll1 foo(ll1);
    ll2 foo(ll2);
};

A::ll1 A::foo(ll1) {

}

A::ll2 A::foo(ll2) {
    
}

#endif // _TEST_H_
```

前置声明需要写在命名空间内，如果类 `Evnet` 在命名空间 `A` 内，则在其他文件中前置声明 `Event`  则需要将该前置声明写在 `namespace A {}` 内。

对于 `namespace` 应尽量少用 `using namespace`，以免污染命名空间。

静态成员变量受访问限定符限制。静态成员函数在实现时，需要脚上类名作用域。

`using namespace` 使用的命名空间受命名空间影响。

如在函数中使用 `__LINE__` 宏，在其他位置调用该函数，则该宏的结果是一样的，所以在宏定义中使用 `__LINE__` 宏，才能知道调用位置。

---

类中定义类或结构体不必 `private`，因为类或结构体只是类型定义。

---

```c
struct A {
    struct Val {
        int x;
    } val;
};
```

`struct A` 结构体中声明了 `Val` 结构体的变量。

---

`override` 关键字要在修饰函数的 `const` 关键字之后。

---

C++11 引入的一种强类型枚举类型：

```cpp
enum class State {
    START,
    STOPPED
};
State s;
```

运算符和操作符时一样的，只是翻译不同。

`this` 指针的有效性：在成员函数内部，编译器假设 `this` 指针总是有效的，即指向某个对象。所以在成员函数内部对 `this` 指针进行检查是冗余操作。应该在调用对象时检查对象的有效性。

---

如项目名称或路径修改后，cmake 生成的 build 目录的构建文件需要重新生成。

---

重写基类虚函数，建议位于 `protected` 访问限制符下，用于区分，同时该类也可以再次被继承。

---

类成员变量初始化顺序

错误的初始化顺序：

```cpp
// server.h
class Server {
public:
    Server(net::io_context &, unsigned short &);
    // ...
private:
    tcp::acceptor acceptor_;
    net::io_context &ioc_;
    tcp::socket socket_;
};
```

```cpp
// server.cpp
Server::Server(net::io_context &ioc, unsigned short &port) : 
    ioc_(ioc),
    acceptor_(ioc_, tcp::endpoint(tcp::v4(), port)),
    socket_(ioc_) {

}
```

正确的初始化顺序：

```cpp
// server.h
class Server {
public:
    Server(net::io_context &, unsigned short &);
    // ...
private:
    net::io_context &ioc_;
    tcp::acceptor acceptor_;
    tcp::socket socket_;
};
```

```cpp
// server.cpp
Server::Server(net::io_context &ioc, unsigned short &port) : 
    ioc_(ioc),
    acceptor_(ioc_, tcp::endpoint(tcp::v4(), port)),
    socket_(ioc_) {

}
```

或者：

```cpp
// server.h
class Server {
public:
    Server(net::io_context &, unsigned short &);
    // ...
private:
    tcp::acceptor acceptor_;
    net::io_context &ioc_;
    tcp::socket socket_;
};
```

```cpp
// server.cpp
Server::Server(net::io_context &ioc, unsigned short &port) : 
    acceptor_(ioc, tcp::endpoint(tcp::v4(), port)),
    ioc_(ioc),
    socket_(ioc) {

}
```

---

当出现未定义方法时，特别注意检查 CMake  等配置文件是否将新增的文件添加进行编译。

---

什么时候需要封装数据：当数据的修改会对整个对象的其他内容产生影响时，这个数据需要封装。

---

当遇到文件无法读取的时，如文件位于项目根目录下，且文件路径也位于项目根目录下，则需将文件移动至可执行文件的目录下。

---

当派生类无法访问基类的公有或保护方法时，检查继承的访问限定符。

---

智能指针所包含类型不能只前置声明。

---

`unordered_map` 的 `operator[]` 没有 const 方法。当类成员函数是常函数，且类中有 `unordered_map` 成员变量时，无法使用 `operator[]` 方法，因为该方法可能修改类成员变量。

---

`friend class ClassName` 与 `friend ClassName` 语义相同

---

CMake 配置项目时，遇到未找到定义时，检查是否将源文件加入编译

---

？虚析构函数重写，子类不重写，不会变成虚类

---

`namespace AAA = BBB;` 命名空间取别名

`using CCC::type;` 使用 `CCC` 命名空间下的 `type` 类型，引入命名空间中的符号

`using namespace DDD;` 使用命名空间

---

`friend` 不受访问限制符影响

---

多线程中，当子线程还未执行时，传入子线程的参数的作用可能结束

---

TLV 协议

```
| Type (1 byte) | Length (1 byte) | Value (variable) |
```

---

`sizeof(array)` 数组未退化为指针，输出 array 所占内存大小。

---

```cpp
class A : public std::enable_shared_from_this<A> {
    A() {
        foo(std::shared_ptr<A>(this)) {} // warn
        foo(std::make_shared<A>(this)) {} // warn
        foo(shared_from_this()) {}
    }
};
void foo(std::shared_ptr<A> ptr) {
    
}
```

使用 `shared_from_this()` 前提需要类型构造完成

`std::bind` 按值绑定，绑定成员函数时，需要指定 `this` 对象。

```cpp
std::bind(&ClassName::Method, this);
```

---

`using` 设置类型别名，在类中受受顺序影响。

`using namespace::class;` 直接使用命名空间下的指定类型。

---

`friend` 不受访问限定符影响，友元关系不能继承。

---

`using` 声明只能在全局作用域（命名空间作用域）或函数作用域（包括成员函数作用域）。

类作用域中使用 `using` 声明会导致编译错误，如果允许这种操作，那么就会在类中引入某个类型，此时就可能和类中已有类型发生命名冲突。

---

```cpp
namespace {
void foo();
}
```

与

```cpp
static void foo();
```

效果类似，保证函数在当前编译单元使用，避免与其他文件的同名函数发生冲突。

---

在函数结束后，局部指针变量将被销毁，因此将其置空没有意义

---

`vscode` tab 键失效，`ctrl` + `M`

---

```cpp
typedef short PACK_LEN_TYPE;
using PACK_LEN_TYPE = short;
```

---

`inline` 允许变量或函数在多个翻译单元中定义而不会导致链接错误，使每个编译单元都有自己的一份副本。

`extern` 声明一个变量或函数在其定义的地方，通常告诉编译器该变量或函数的定义在其他的翻译单元中。

`inline` 修饰变量是 C++17 引入的特性。

---

`std::shared_ptr` 变量重新分配时，原先的内存会自动销毁。，`std::shared_ptr` 位于类中时，当类析构后，内存会自动回收。

---

`std::shared_ptr` 构造的第二个参数为删除器（可调用对象）。

---

常量引用 `std::shared_ptr` 无法增加引用计数。

---

常量成员函数可以修改 `mutable` 修饰的成员变量。

---

`std::bind` 绑定的参数会去除引用。

---

智能指针赋值为空，等价于提前回收智能指针管理的资源。

---

函数没有返回类型为 `void`，使用 `exit()` 返回指定值。

---

使用 `const_cast` 移除返回 `const &` 中 `const` 时需确保对象不是常量。

---

`std::ifstream` 打开文件后，再次打开别的文件时，需要将原先打开的文件关闭。

---

服务端关闭连接时，关闭发送端。防止大量 `close wait established`

---

C++11 不允许在 `for (auto v : vec)` 中修改 `vec`，这是未定义行为。

---

使用阻塞 IO 模型，每个 fd 需要一个线程进行处理

IO 多路复用：单个线程/进程能同时处理多个 IO 请求

---

```cpp
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    if (pass_line_edit_->hasFocus() && !pass_line_edit_->geometry().contains(event->pos())) {
        pass_line_edit_->clearFocus();
    }
}
```

调用父类默认处理时，不能使用 `this->mousePressEvent(event)`，因为这是调用 `MainWindow::mousePressEvent`。

---

当发现 `QWidget` 的子类无法使用 `addWidget()` 时，检查继承限定符。

当子类**对象**无法使用父类的公有方法时，检查继承限定符。

---

VSCode SSH 连接服务器时，Linux 服务器需要有 `wget` 和 `tar` 包。

---

```cpp
#include <vector>
#include <iostream>

int main(int argc, char const *argv[])
{
    int a[4] = {1, 2, 3, 4};
    std::vector<int *> v{a, a + 1, a + 2, a + 3};
    for (auto it = v.begin(); it != v.end(); ++it)
    {
        std::cout << **it << std::endl;
        it = v.erase(it);
    }
    return 0;
}
```

---

abi、extern "C"

OpenMP

SFML

jom、ninjia、CMake、msbuild、make、nmake、qmake

---

`switch` 的多个 `case` 是共用一个作用域的
