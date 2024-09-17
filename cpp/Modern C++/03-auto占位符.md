### 1. 重新定义的 auto

C++98 标准中 `auto` 关键字就存在，但是该 `auto` 用于声明自动变量（自动生命周期）。

C++11 标准重新定义 `auto` 关键字，用于声明变量时根据初始化表达式自动推导变量的类型、声明函数时函数的返回值的占位符。

使用 `auto` 关键字注意事项：

1. 当用 `auto` 关键字声明多个变量时，编译器遵循由左往右的推导规则，以最左边的表达式推导 `auto` 的具体类型。

   ```cpp
   int a = 1;
   auto *pa = &a, b = 2;
   ```

   `&a` 类型为 `int *`，所以 `pa` 的类型被推导为 `int *`，`auto` 被推导为 `int`，所以声明 `int` 类型变量。

   ```cpp
   int a = 1;
   auto *pa = &a, b = 2.0; // compilation failed
   ```

   单独 `int b = 2.0;` 编译器会进行缩窄转换，不会编译失败。

2. 使用条件表达式初始化 `auto` 声明的变量时，编译器总是使用表达能力更强的类型。

   ```cpp
   auto i = true ? 5 : 8.0; // the data type of i is double
   ```

3. `auto` 无法声明**非静态成员变量**。

   ```cpp
   struct Type1 {
       auto x = 1; // compilation failed
   }
   struct Type2 {
       static const auto x = 1;
   }
   struct Type3 {
       static inline auto x = 1; // C++17
   }
   ```

4. C++20 标准允许使用 `auto` 声明函数形参，C++14 标准允许 lambda 表达式使用 `auto` 声明形参。

   ```cpp
   void foo(auto x) {} // C++20
   auto f = [](auto x) {}; // C++14
   ```
   
5. 使用 `auto` 声明变量时必须**初始化**，否则无法推导，编译错误：

   ```cpp
   auto x; // compilation failed
   auto y = 1.1;
   ```

`auto` 关键字可以与 `new` 关键字结合，但不建议使用。

```cpp
auto i = new auto(1);
auto *p = new auto(1);
```

`auto(1);` 中 `auto` 被推导为 `int` 类型，通过 `int *` 推导 `i` 和 `p` 的类型。

### 2. 变量推导规则

如果 `auto` 声明的变量是按值初始化（没有引用和指针修饰），则推导出的 `auto` 类型会忽略 cv 限定符，`auto` 本身支持添加 cv 限定符。

```cpp
const int i = 1;
auto a = i;       // auto 推导为 int 类型
auto &b = i;      // auto 推导为 const int 类型
auto *c = &i;     // auto 推导为 const int 类型
const auto d = i; // auto 推导为 int 类型
```

`i` 是 `const int` 类型，`a` 按值初始化，所以忽略 cv 限定符，`a` 的类型为 `int` 而不是 `const int`。

> 这一切很合理，因为一个被 `const` 修饰的常量是不应该被修改的，如果 `auto &b = i;` 没有推导出 `auto` 类型为 `const int` 则是可以通过 `i` 的引用 `b` 对 `i` 进行修改的，如果是这样则 `const` 意义何在（指针同理）。

如果 `auto` 声明变量时目标对象是引用，则引用被忽略。

```cpp
int i = 1;
int &ri = i;
auto x = ri; // auto 推导为 int
```

如果 `auto` 和万能引用声明变量时，对于左值会将 `auto` 推导为引用类型。

```cpp
int i = 1;
auto &&j = i; // auto 推导为 int &
auto &&k = 2; // auto 推导为 int
```

如果 `auto` 声明变量时目标对象是一个数组或函数，则 `auto` 被推导为对应指针类型。

```cpp
int a[3];
auto pa = a; // auto 推导为 int *

void func(int) {}
auto pf = func; // auto 推导为 void (__cdecl * )(int)
```

当 `auto` 与列表初始化组合时，分两种情况：

1. 直接使用列表初始化，列表中必须为单个元素，否则无法编译，`auto` 类型被推导为单元素类型。

   ```cpp
   auto x1 {1};    // auto 推导为 int
   auto x2 {1, 2}; // compilation failed
   ```

2. 用等号加列表初始化，列表中可以包含单个或多个元素，`auto` 推导为 `std::initializer_list<T>`，其中 `T` 为元素类型，列表中类型必须相同。

   ```cpp
   auto x3 = {1, 2, 3};   // auto 推导为 std::initializer_list<int>
   auto x4 = {1, 2, 3.3}; // compilation failed
   ```

```cpp
#include <iostream>

class Base {
public:
    virtual void foo() {
        std::cout << "Base foo" << std::endl;
    }
};

class Derived : public Base {
public:
    void foo() override {
        std::cout << "Derived foo" << std::endl;
    }
};

int main(int argc, char const *argv[]) {
    Base *p = new Derived();
    auto v = *p;
    v.foo(); // "Base foo"

    auto pv = p;
    pv->foo(); // "Derived foo"

    auto &rv = p;
    rv->foo(); // "Derived foo"
    return 0;
}
```



### 3. 返回类型推导

C++11 标准允许函数返回类型为 `auto`，但不能仅仅使用 `auto` 作为函数返回类型，需要采用后置返回类型，该标准中 `auto` 作为函数返回类型的占位符并不对函数返回类型进行推导，必须使用返回类型后置的形式指定返回类型：

```cpp
auto foo(int a, int b) { return a + b; } // C++11 compilation failed
auto foo(int a, int b) -> decltype(a + b) {
    return a + b;
}
```

C++14 标准允许函数返回类型为 `auto`，但是需要保证返回值类型相同，否则编译失败：

```cpp
auto foo(int a, int b) { return a + b; }

auto foo2() {
    return 1;
    return 1.1; // compilation failed
}
```

### 4. 合理使用 auto

对于复杂度类型使用 `auto`，如 lambda 表达式、bind 等。

```cpp
auto f = [](int a) {std::cout << a << endl;};
auto bf = std::bind([](int a) {std::cout << a << std::endl;}, 10);
```

对于明显的声明变量初始化的类型使用 `auto`，如容器迭代器。

```cpp
std::map<std::string, int> mp; mp["111"] = 111; mp["222"] = 222;

// for (std::map<std::string, int>::iterator it = mp.begin(); it != mp.end(); ++it) {
for (std::map<std::string, int>::const_iterator it = mp.begin(); it != mp.end(); ++it) {
    std::cout << it->first << " " << it->second << std::endl;
}

for (std::pair<const std::string, int> &p : mp) {
// for (std::pair<std::string, int> &p : mp) { // compilation failed
    std::cout << p.first << " " << p.second << std::endl;
}

for (auto &p : mp) {
    std::cout << p.first << " " << p.second << std::endl;;
}
```

### 5. lambda 中使用 auto

C++14 标准允许 lambda 表达式使用 `auto` 声明形参。

```cpp
auto f = [](auto a, auto b) { return a + b; }
auto res = f(1.1, 1);
```

lambda 表达式返回 `auto` 引用。

```cpp
auto f = [](int &a) -> auto & { return a; }
auto a1 = 1;
auto &a2 = f(a1);
assert(&a1 == &a2);
```



### 6. 非类型模板占位符

C++17 标准允许在非类型模板形参的占位符中使用 `auto`，但必须保证推导出的类型可以作为模板形参，否则编译失败。

```cpp
#include <iostream>

template<auto N> // C++17
void foo() {
    std::cout << N << std::endl;
}

int main() {
    foo<1>();
    foo<1.1>(); // compilation failed, C++20 allow
    foo<'c'>();
    return 0;
}
```

