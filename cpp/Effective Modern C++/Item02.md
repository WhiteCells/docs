### Item02: Understand auto type deduction (理解 auto 类型推导)

auto 类型推导和模板类型推导有一个直接的映射关系。它们之间可以通过一个非常规范非常系统化的转换流程来转换彼此。

在 Item1 中，模板类型推导使用下面这个函数模板解释：

```cpp
template<typename T>
void f(ParamType param);

f(expr);
```

在 f 的调用中，编译器使用 expr 推导 T 和 ParamType。当一个变量使用 auto 进行声明时，auto 扮演模板的角色，变量类型说明符扮演 ParamType 角色。

考虑这个例子：

```cpp
auto x = 27;
```

这里的 x 的类型说明符是 auto，另一方面，在这个声明中：

```cpp
const auto cx = x;
```

类型说明符是 const auto，另一个：

```cpp
const auto &rx = x;
```

类型说明符是 const auto &。在这些例子中要推导 x、cx、rx 的类型，编译器的行为看起来就像认为这里每个声明都有一个模板，然后使用合适的初始化表达式进行处理：

```cpp
template<typename T> // 理想化模板用来推导 x 的类型
void funcForX(T param);

funcForX(27);

template<typename T> // 理想化模板用来推导 cx 的类型
void funcForCX(const T param);

funcForCX(x);

template<typename T> // 理想化模板用来推导 rx 的类型
void funcForRX(const T &param);

funcForRX(x);
```

auto 类型推导出列一个例外，其他情况和模板类型推导一样。

- 类型说明符是一个指针或引用但不是通用引用
- 类型说明符是一个通用引用
- 类型说明符既不是指针也不是引用

```cpp
auto x = 27;          // Item1 case3
const auto cx = x;    // Item1 case3
const auto &rx = cx;  // Item1 case1
```

Item1 讨论并总结了数组和函数作为模板函数形参类型推导的结果，哪些内容也适用于 auto 类型推导

```cpp
const char name[] =     // name 的类型是 const char[13] 
'R. N. Briggs'; 

auto arr1 = name;       // arr1 的类型是 const char *
auto &arr2 = name;      // arr2 的类型是 const char(&)[13]

void someFunc(int, double);

auto func1 = someFunc;   // func1 的类型是 void(int, double)
auto &func2 = someFunc;  // func2 的类型是 void(&)(int, double)
```

接下来要讨论一个例外。

从一个简单的例子开始，如果想用一个 int 值 27 来声明一个变量，C++98 提供两种选择：

```cpp
int x1 = 27;
int x2(27);
```

C++11 由于也添加了用于支持统一初始化 (uniform initialization) 的语法：

```cpp
int x3 = {27};
int x4{27};
```

Item5 解释了使用 auto 说明符代替指定类型说明符的好处，所以将上面声明中的 int 替换为 auto：

```cpp
auto x1 = 27;
auto x2(27);
auto x3 = {27};
auto x4{27};
```

这些声明都能通过编译，但是不像替换之前那样有相同的意义：

```cpp
auto x1 = 27;   // 类型是 int，值是 27
auto x2(27);    // 同上
auto x3 = {27}; // 类型是 std::initializer_list<int>，值是 {27}
auto x4{27};    // 同上
```

当 auto 声明的变量使用花括号进行初始化，auto 类型推导会推导出 auto 的类型为 std::initializer_list。如果 auto 的类型不能被成功推导（比如花括号里包含的是不同类型的变量）会无法通过编译：

```cpp
auto x5 = {1, 2, 3.0}; // auto 推导失败
```

上述代码会类型推导失败，但是需要认识到这里发生了两种类型推导：

1. 由于 auto 的使用，x5 的类型不得不被推导，因为 x5 使用花括号的方式进行初始化，x5 必须被推导为 std::initializer_list。
2. 模板类型推导，std::initializer_list 是一个模板，std::initializer_list 会被实例化，所以这里 T 也会被推导

对于花括号的处理是 auto 类型推导和模板类型推导唯一不同的地方，当使用 auto 的变量使用花括号的语法进行初始化，会推导出 std::initializer_list 的实例化，但是对于模板类型推导这样就行不通：

```cpp
template<typename T>
void f(T param);

f({11, 23, 9}); // 不能推导出 T
```

如果指定 T 是 std::initializer_list 而留下未知 T，模板类型推导就能正常工作：

```cpp
template<typename T>
void f(std::initializer_list<T> init_list);

f({11, 23, 9}); // T 被推导为 int，init_list 的类型被推导为 std::initializer_list<int>
```

C++14 允许 auto 用于函数返回值并会被推导 (Item3)，而且 C++14 的 lambda 函数也允许在形参中使用 auto，这些情况虽然表面上使用的是 auto 但实际上是使用与模板类型推导相同的规则，下面的代码无法通过编译：

```cpp
auto createInitList() {
    return {1, 2, 3}; // 推导失败
}
```

同样在 C++14 的 lambda 函数中这样使用 auto 也不能通过编译：

```cpp
std::vector<int> v;

auto resetv = [&v](const auto &new_value) { v = new_value; }; // C++14

reset({1, 2, 3}); // 推导失败
```

记住：

- auto 类型推导推导通常和模板类型推导相同，但是 auto 类型推导假定是花括号初始化代表 std::initializer_list 而模板类型推导不这样做
- 在 C++14 中 auto 允许出现在函数返回值或者 lambda 函数形参中，但是它的工作机制是模板类型推导那一套方案
