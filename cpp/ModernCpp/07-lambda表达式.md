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

**[captures]** 捕获列表，可以捕获当前函数作用域的变量，变量之间用逗号分隔，有按值捕获和引用捕获。

**(params)** 可选参数列表

**specifiers** 可选限定符

**exception** 可选异常说明符

**ret** 可选返回值类型

**{ body }** lambda 表达式函数体

在 C++14 标准和 C++17 标准中对 lambda 表达式又进行了拓展。

### 2. 捕获列表

作用域