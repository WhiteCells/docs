虚拟 函数 "dock::ControlDockWindow::~ControlDockWindow" 的异常规范与重写 函数 "QWidget::~QWidget" 的异常规范不兼容

> 析构函数已存在

方法实现时，const 限定符需指明，static 修饰符不必指明，override 不必指明。

父类变量由父类初始化，子类能使用初始化列表方式只能初始化自己的成员变量，不能是父类的非静态成员变量。

即使析构函数被声明为纯虚函数也需要给出定义，所以析构函数不必声明为纯虚函数，只需是虚函数。

父类纯虚函数（除纯虚析构），派生类需要提供其实现，如不提供实现，则派生类会成为抽象类，无法实例化。

构造函数不能被声明为虚函数，因为在对象的创建过程中，虚拟机制还没有开始工作，也就是说，在构造函数调用期间，对象的动态类型尚未确定。

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

模板类的定义和实现需要放在同一个文件中。

纯虚函数存在实现就不再是虚函数，父类不是抽象类，子类也不会因为没有重写而成为抽象类。

常量对象其成员必须存在初始化值。

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

> 前置声明只适用于指针和引用，因为在声明指针和引用时不需要知道其完整的大小和布局。

使用 `using` 或 `typedef` 设置类型别名，该类型别名受访问限定符影响：

```cpp
class C {
    typedef long long ll1;
    using ui1 = int;
public:
    typedef long long ll2;
    using ui2 = int;
};

class D : C {
    ll1 a = 1; // error
    ll2 b = 1;
    ui1 c = 1; // error
    ui2 c = 1;
};
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

