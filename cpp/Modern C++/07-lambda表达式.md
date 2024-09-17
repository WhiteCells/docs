### 1. lambda 表达式语法

C++11 支持 lambda 表达式，在此之前需要使用 Boost.Bind 或 Boost.Lambda 来实现 lambda 表达式的功能，但实现较为复杂。

C++ 对 lambda 的需求量较大，如 STL 中需要传入谓词的算法函数，在 C++11 之前需要编写纯函数或仿函数来实现谓词，但是其无法直接应用到函数调用的实参中，需要先定义然后实现最后调用谓词。

```cpp
#include <iostream>
#include <algorithm>
#include <vector>

bool isPositive2(int a) {
    return a > 0;
}

int main(int argc, char *argv[]) {
    std::vector<int> v {-1, 0, 1};

    struct isPositive1 {
        bool operator()(int a) {
            return a > 0;
        }
    };

    auto iter1 = std::find_if(v.begin(), v.end(), isPositive1());
    auto iter2 = std::find_if(v.begin(), v.end(), isPositive2);
    // use lambda
    auto iter3 = std::find_if(v.begin(), v.end(), [](int a) { return a > 0; });

    std::cout << *iter1 << std::endl;
    std::cout << *iter2 << std::endl;
    std::cout << *iter3 << std::endl;
    return 0;
}
```

lambda 基本语法：

```
[captures] (params) specifiers exception -> ret { body }
```

**[captures]** 捕获列表，可以捕获当前函数作用域的变量，变量之间用逗号分隔，有按值捕获和引用捕获

**(params)** 可选参数列表

**specifiers** 可选限定符

**exception** 可选异常说明符

**ret** 可选返回值类型

**{ body }** lambda 表达式函数体

在 C++14 标准和 C++17 标准中对 lambda 表达式又进行了拓展。

### 2. 捕获列表

捕获列表中的变量存在于两个作用域，lambda 表达式定义的函数作用域和 lambda 表达式函数体的作用域，前者为了捕获变量，后者为了使用变量。

标准规定能捕获的变量必须是一个**自动存储类型**，简单理解为**非静态**的**局部**变量：

```cpp
int x = 1;

int main(int argc, char *argv[]) {
    int y = 1;
    static int z = 1;
    auto foo = [x, y, z] {}; // compilation failed
    return 0;
}
```

静态变量和全局变量直接使用即可：

```cpp
int x = 1;

int main(int argc, char *argv[]) {
    int y = 1;
    static int z = 1;
    auto foo = [y] { return x + y + z; };
    return 0;
}
```

如果将 lambda 表达式定义在全局，则 lambda 表达式的捕获列表必须为空，因为全局作用域没有自动存储类型。

lambda 表达式既可以**捕获值**也可以**捕获引用**：

```cpp
int main(int argc, char *argv[]) {
    int x = 1, y = 1;
    // capture value
    auto foo1 = [x, y] { return x + y; };
    // capture reference
    auto foo2 = [&x, &y] { return x + y; };
    return 0;
}
```

**以捕获值的方式捕获的变量不能对变量的值进行修改**：

```cpp
int main(int argc, char *argv[]) {
    int x = 1;
    // capture value
    auto foo1 = [x] { x += 1; }; // compilation failed
    // capture reference
    auto foo2 = [&x] { x += 1; };
    return 0;
}
```

lambda 表达式是一个**常量函数**，捕获的变量默认为常量，值捕获时，变量本身就是值，所以修改值会发生错误，引用捕获时，捕获变量实际上是一个引用，在 lambda 表达式 body 修改的并不是引用本身，而是引用的值。

使用说明符 `mutable` 说明符可以移除 lambda 表达式的常量性：

```cpp
#include <iostream>

int main(int argc, char *argv[]) {
    int x = 1;
    // capture value
    auto foo1 = [x]() mutable { x += 1; };
    return 0;
}
```

在增加 `mutable` 说明符时，加上了 `()`，这是因为 lambda 表达式规定，如果存在说明符，则形参列表不能省略。

捕获值和捕获引用存在本质的区别：

```cpp
#include <iostream>

int main(int argc, char *argv[]) {
    int x = 1, y = 1;
    auto foo = [x, &y]() mutable {
        x += 1;
        y += 1;
        printf("%d %d\n", x, y);
    };
    foo(); // 2 2
    printf("%d %d\n", x, y); // 1 2
    foo(); // 3 3
    printf("%d %d\n", x, y); // 1 3
    return 0;
}
```

虽然 lambda 表达式内修改 x 不会影响外部 x，但是会影响下次调用 lambda 表达式时 x 的值。

**值捕获的变量**在 lambda 表达式定义的时候已固定，修改外部变量的值，lambda 表达式捕获的值不会再变化：

```cpp
#include <iostream>

int main(int argc, char *argv[]) {
    int x = 1, y = 1;
    auto foo = [x, &y]() mutable {
        x += 1;
        y += 1;
        printf("%d %d\n", x, y);
    };
    x = 10;
    y = 10;
    foo(); // 2 11
    return 0;
}
```

lambda 表达式中还有 3 中特殊的捕获方法，分别是 `[this]`、`[=]`、`[&]`。

捕获 `this` 可以使用 `this` 类型的成员变量和函数：

```cpp
#include <iostream>

class A {
public:
    void print() { printf("%d\n", x); }
    void test() {
        auto foo = [this] {
            print();
        };
        x = 10;
        foo();
    }

private:
    int x;
};

int main(int argc, char *argv[]) {
    A a;
    a.test(); // 10
    return 0;
}
```

`[=]` 为捕获全部变量的值：

```cpp
#include <iostream>

int main(int argc, char *argv[]) {
    int x = 1;
    auto foo = [=] {
        // x += 1; // compilation failed
        return 0;
    }();
    return 0;
}
```

`[&]` 捕获全部变量的引用：

```cpp
#include <iostream>

int main(int argc, char *argv[]) {
    int x = 1;
    auto foo = [&] {
        x += 1;
        return 0;
    }();
    std::cout << x << std::endl; // 2
    return 0;
}
```

### 3. 无状态 lambda 表达式

C++ 标准中无状态 lambda 表达式（捕获列表为空）可以隐式转换为函数指针：

```cpp
int main(int argc, char *argv[]) {
    auto f1 = [](void(*)()) {};
    f1([] {});

    auto f2 = [](void(&)()) {};
    f2(*[] {});
    return 0;
}
```

### 4. 广义捕获

C++14 标准中定义了广义捕获，广义捕获是两种捕获方式：简单捕获和初始化捕获。

C++14 引入初始化捕获，解决了简单捕获只能捕获 lambda 表达式定义上下文的变量，而无法捕获表达式结果及自定义捕获变量名：

```cpp
int main() {
    int x = 1;
    auto foo = [x = x + 1] { return x; };
}
```

以上代码在 C++14 标准之前是无法通过编译，C++11 只支持简单捕获。捕获列表中 `x = x + 1` 有两个作用域，等号左侧的变量 `x` 存在于 lambda 表达式的作用域，等号右侧的变量 `x` 存在于 main 函数的作用域，lambda 表达式中无法使用 main 函数作用域下的 `x`。

初始化捕获可以使移动操作减少运行开销：

```cpp
std::string str = "string";
auto foo = [s = std::move(str)] { return s; };
```

异步调用 `this` 对象，防止 lambda 表达式被调用时因原始 `this` 对象被析构造成未定义的行为：

```cpp
#include <iostream>
#include <future>

class Work {
public:
    Work() : value_(1) {}
    std::future<int> spawn() {
        return std::async([=]() -> int {return value_;});
    }
private:
    int value_;
};

std::future<int> foo() {
    Work work;
    return work.spawn();
    // work destruct
}

int main(int argc, char *argv[]) {
    std::future<int> f = foo();
    f.wait();
    std::cout << "f.get() = " << f.get() << std::endl;
    return 0;
}
```

在 C++11 标准中 `f.get()` 实际上返回了 32767，为了解决这个问题，需要将对象复制到 lambda 表达式内：

```cpp
class Work {
public:
    Work() : value_(1) {}
    std::future<int> spawn() {
        return std::async([=, tmp = *this]() -> int {return tmp.value_;});
    }
private:
    int value_;
};
```

将 `*this` 复制到 tmp 对象中，即使 `this` 所指的对象析构了也不会影响 lambda 表达式的计算。

### 5.  泛型 lambda 表达式

C++14 标准使 lambda 具备模板函数的能力，称为泛型 lambda 表达式：

```cpp
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    auto foo = [](auto a) { return a; };
    int i = foo(1);
    std::string str = foo("string");
    std::cout << str << i << std::endl;
    return 0;
}
```

### 6. 常量 lambda 表达式和捕获 *this

C++17 标准对 lambda 表达式的两处增强：常量 lambda 表达式和捕获 `*this`。

使用类中成员需要初始化捕获 `*this` 对象，在捕获列表复制一份 `*this` 指向的对象到 `tmp`，然后使用 `tmp`，为了更方便的复制和使用 `*this` 对象，C++17 可以在捕获列表中直接添加 `*this`，然后在 lambda 表达式函数体中直接使用 `this` 所指向对象的成员：

```cpp
class Work {
public:
    Work() : value_(1) {}
    std::future<int> spawn() {
        return std::async([=, *this]() -> int {return value_;});
    }
private:
    int value_;
};
```

`*this` 语法让程序生成了一个 `*this` 对象的副本并存储在 lambda 表达式内。

### 7. 捕获 [=, this]

C++20 标准引入 `[=, this]` 语法。

`[=]` 可以捕获 `this` 指针，`[=, *this]` 会捕获 `this`对象的副本，但是不易区分，所以 C++20 标准引入 `[=, this]` 语法，实际含义与 `[=]` 相同，目的是为了区分 `[=, *this]`。

C++20 标准强调以 `[=, this]` 代替 `[=]`。

### 8. 模板语法的泛型 lambda 表达式

C++20 标准中添加模板对 lambda 表达式的支持：

```cpp
[]<typename T>(T t) {}
```

### 9. 可构造和可赋值的无状态 lambda 表达式
