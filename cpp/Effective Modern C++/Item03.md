### Item03: Understand decltype (理解 decltype)

从一个简答的例子开始

```cpp
const int i = 0; // decltype(i) 是 const int

bool f(const widget &w); // decltype(w) 是 const widget &
                         // decltype(f) 是 bool(const widget &)

struct Point {
    int x;        // decltype(Point::x) 是 int
    int y;        // decltype(Point::y) 是 int
}

template<typename T>
class vector {
    T &operator[](std::size_t index);
}

vector<int> v;     // decltype(v) 是 vector<int>

if (v[0] == 0)     // decltype(v[0]) 是 int &
```

在 C++11 中，`decltype` 最主要的用途就是用于函数模板返回类型，而这个返回类型依赖形参。举个例子，假设写一个函数，一个参数为容器，一个参数为索引值，这个函数支持使用方括号的方式返回容器中指定索引值的数据，然后在返回索引操作的结果前执行认证用户操作。函数的返回类型应该和索引操作返回的类型相同。

对一个 `T` 类型的容器适用 `operator[]` 通常会返回一个 `T&` 对象，但是 `std::vector`，`operator[]` 不会返回 `bool&`，它会返回一个有名字的对象类型（译注：MSVC 的 STL 实现中返回的是 `std::Vb_reference<std::Wrap_alloc<std::allocator>>`）。对一个容器进行 `operator[]` 操作返回的类型取决于容器本身。

使用 `decltype` 很容易实现上述假设的函数：

```cpp
template<typename Container, typename Index>
auto authAndAccess(Container &c, Index i) -> decltype(c[i]) {
    // authenticateUser();
    return c[i];
}
```

函数名称前面的 `auto` 不会做任何类型推导工作。相反，他只是暗示使用 C++11 的尾置返回类型语法，即在函数形参列表后使用 `->` 符号指出函数的返回类型，尾置返回类型的好处是可以在函数返回类型中使用函数参数相关的信息。在 `authAndAccess` 函数中，返回类型使用了 `c` 和 `i`。如果按照传统的语法将函数返回类型放在函数名称之前，`c` 和 `i` 就未被声明所以不能使用。

C++11 允许自动推导单一语句的 lambda 表达式的返回值，C++14 扩展到允许自动推导所有的 lambda 表达式和函数，甚至他们内含多条语句。对于 `authAndAccess` 函数在 C++14 标准下可以忽略尾置返回类型，只留下一个 `auto` 。这种形式下 `auto` 不再进行 `auto` 类型推导，而是编译器根据函数实现推导出函数的返回类型。

```cpp
template<typename Container, typename Index> // C++14 版本
auto authAndAccess(Container &c, Index i) {
    // authenticateUser();
    return c[i];
}
```

Item2 解释了函数返回类型中使用 `auto` 编译器实际上使用的模板类型推导的规则，但是 `operator[]` 对于大多数 `T` 类型的容器返回的是一个 `T&`，但是 Item1 解释了在模板类型推导期间，如果表达式是一个引用那么引用将会被忽略。基于这些郭泽，会导致下面的代码编译失败：

```cpp
std::deque<int> d;
authAndAccess(d, 5) = 10; // 无法通过编译
```

模板类型推导忽略了引用部分，因此返回类型为 `int`。函数返回的值是一个右值，将 10 赋值给右值，所以代码无法编译。

想要返回类型为 `T&`，需要使用 `decltype` 类型推导来推导返回值，C++14 通过使用 `decltype(auto)` 说明符使得类型被暗示时使用 `decltype` 类型推导的规则，`auto` 说明符表示这个类型会被推导，`decltype` 说明 `decltype` 的规则会被引用到这个推导的过程中。因此可以这样实现 `authAndAccess`：

```cpp
template<typename Container, typename Index> // C++14 版本
decltype(auto) authAndAccess(Container &c, Index i) {
    // authenticateUser();
    return c[i];
}
```

现在 `authAndAccess` 将会真正的返回 `c[i]` 类型，一般情况下 `c[i]` 返回 `T&`，`authAndAccess` 也会返回 `T&`，特殊情况下 `c[i]` 返回一个对象，`authAndAccess` 也会返回一个对象。

`decltype(auto)` 的使用不仅仅局限于函数返回类型，当想对初始化表达式使用 `decltype` 推导的规则时也可以使用：

```cpp
Weight w;
const Weight &cw = w;

auto my_weight1 = cw;           // auto 类型推导
                                // my_weight1 类型为 Weight

decltype(auto) my_weight2 = cw; // decltype 类型推导
                                // my_weight2 类型是 const Weight &
```

 `decltype(auto)` 版本的 `authAndAccess` 容器通过传引用的方式传递非常量左值引用，返回一个引用允许用户可以修改容器。但这意味着在这个函数里不能传值调用，右值不能绑定到左值引用上（除非这个左值引用是一个 const）

一个右值容器，是一个临时对象，通常会在 `authAndAccess` 调用结束被销毁，如果 `authAndAccess` 返回引用就会成为一个悬置（dangle）引用。但是使用 `authAndAccess` 传递一个临时对象也并不是没有意义，有时用户只是想简单的获得临时容器中的一个元素的拷贝：

```cpp
std::deque<std::string> makeStringDeque(); // 工厂函数

auto s = authAndAccess(makeStringDeque(), 5); // 从工厂函数中获取第五个元素的拷贝并返回
```

想支持传值调用，就需要将声明进行修改，使得它支持左值和右值。一个方法是使用重载（一个函数重载声明为左值引用，另一个声明为右值引用），但是这样就需要维护两个重载函数。另一个方法是使 `authAndAccess` 的引用可以绑定左值和右值，使用通用引用进行声明：

```cpp
template<typename Container, typename Index>
decltype(auto) authAndAccess(Container &&c, Index i);
```

在这个模板中不知道操作的容器类型是什么，相当于忽略了索引对象的可能，对于一个未知类型的对象使用传值对程序的性能有极大的影响，在这个例子中还会造成不必要的拷贝、对象切片行为。就容器索引而言，遵照标准模板库对于索引的处理是有理由的，所以坚持传值调用。

最后需要更新模板的实现，让它能听从 Item25 的告诫应用 `std::forward` 实现通用引用：

```cpp
template<typename Container, typename Index>  // 最终 C++14 版本
decltype(auto) authAndAccess(Container &&c, Index i) {
    // authenticateUser();
    return std::forward<Container>(c)[i];
}
```

上述代码要求编译器支持 C++14，下面是使用 C++11，与 C++14 相似，除了需要指定函数返回类型：

```cpp
template<typename Container, typename Index> // C++11
auto authAndAccess(Container &&c, Index i) -> decltype(std::forward<Container>(c)[i]) {
    // authenticateUser();
    return std::forward<Container>(c)[i];
}
```

对一个名字使用 `decltype` 将会产生这个名字被声明的类型。

名字是左值表达式，`decltype` 确保产生的类型总是左值引用。

```cpp
int x = 0;
```

`x` 是一个变量的名字，所以 `decltype(x)` 是 int，但是如果用一个小括号包覆这个名字，比如 `(x)` 就会产生一个比名字更复杂的表达式。对于名字来说，`x` 是一个左值，C++11 定义了表达式 `(x)` 也是一个左值，因此 `decltype((x))` 是 `int&`。使用小括号包覆一个名字可以改变 `decltype` 对于名字产生的效果。

由于 C++14 允许 `decltype(auto)` 的使用，这意味着函数返回语句中细微的变化就可以影响返回类型的推导：

```cpp
decltype(auto) f1() {
    int x = 0;
    return x; // decltype(x) 是 int, 所以 f1 返回 int 类型
}

decltype(auto) f2() {
    int x = 1;
    return (x); // decltype((x)) 是 int&, 所以 f2 返回 int& 类型
}
```

注意 f2 返回返回类型引用了一个局部变量，这是未定义行为。

当使用 `decltype(auto)` 的时候需要加倍小心，在表达式中无足轻重的细节将会影响类型的推导。通常 `decltype` 都会产生想要的结果，尤其对一个名字使用 `decltype` 时，因为在这种情况下，`decltype` 只做一件事：产出名字的声明类型。

记住：

- `decltype` 总是不加修改的生成变量或者表达式的类型
- 对于 `T` 类型的左值表达式，`decltype` 总是产出 `T` 的引用即 `T&`
- C++14 支持 `decltype(auto)`，就像 `auto` 推导类型，但它使用独特规则进行推导

