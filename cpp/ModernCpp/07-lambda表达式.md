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

以捕获值的方式捕获的变量不能对变量的值进行修改：

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

lambda 表达式是一个常量函数，捕获的变量默认为常量，值捕获时，变量本身就是值，所以修改值会发生错误，引用捕获时，捕获变量实际上是一个引用，在 lambda 表达式 body 修改的并不是引用本身，而是引用的值。

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

**值捕获的变量**在 lambda 表达式定义的时候已固定，修改外部变量的值，lambda 表达式捕获的值就不会再变化：

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

捕获 `this` ，使用在类的成员函数中：

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

```

`[&]` 捕获全部变量的引用：

```cpp

```

### lambda 表达式实现原理
