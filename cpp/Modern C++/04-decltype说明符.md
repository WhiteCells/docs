### 1. typeid 运算符

C++ 标准提供 `typeid` 运算符来获取与目标操作数类型有关的信息。

获取的类型信息会包含一个类型为 `std::type_info` 的对象中，可以调用成员函数 `name` 获取其类型名：

```cpp
int x = 1;
float y = 1.1F;
std::cout << typeid(1).name() << std::endl;
std::cout << typeid(x).name() << std::endl;
std::cout << typeid(x + y).name() << std::endl;
std::cout << typeid(double).name() << std::endl;
```

成员函数 `name` 返回的类型名在 C++ 标准中并**没有明确的规范**，输出的类型名因编译器而异。

使用 `typeid` 运算符的注意事项：

1. `typeid` 的返回值是一个左值，生命周期扩展到程序生命周期结束。

2. `typeid` 返回的 `std::type_info` 删除了复制构造函数，只能获取其引用或指针：

   ```cpp
   auto t1 = typeid(1);   // compilation failed
   auto &t2 = typeid(1);  // auto 推导为 const std::type_info &
   auto *t3 = &typeid(1); // auto 推导为 const std::type_info *
   ```

3. `typeid` 返回值忽略类型的 cv 限定符：

   ```cpp
   const int x = 1;
   int y = 1;
   std::cout << (typeid(x).name() == typeid(y).name()) << std::endl;
   ```

### 2. decltype 说明符

C++11 标准引入了 `decltype` 说明符，使用 `decltype` 说明符可以获取**对象**或**表达式**的类型：

```cpp
int x1 = 0;
decltype(x1) x2 = 0;
std::cout << typeid(x2).name() << std::endl; // i

double x3 = 1.1;
decltype(x1 + x3) x4 = x1 + x3;
std::cout << typeid(x4).name() << std::endl; // d
```

用于推导的表达式不进行运算：

```cpp
int a = 1;
decltype(a++) b = 1;
decltype(++a) c = a;
std::cout << a << std::endl; // 1
```

`decltype` 可以在**非静态成员变量**中使用：

```cpp
struct A {
    int a;
    decltype(a) b;
    double c;
    decltype(a + c) d;
};
```

`decltype` 可以在**函数形参列表及返回值**中使用：

```cpp
int x;
decltype(x) sum(decltype(x) a, decltype(x) b) {
    return a + b;
}
auto r = sum(1, 1);

template<class T1, class T2>
auto sum2(T1 a, T2 b) -> decltype(a + b) { // C++11
    return a + b;
}
auto r2 = sum2(1, 1.1);
```

C++14 中虽然支持 `auto` 作为函数返回类型，且无需后置返回类型，但是 `auto` 作为返回类型存在一些问题：

```cpp
template<class T>
auto returnRef(T &t) {
// auto &returnRef(T &t) { // return reference
    return t;
}

int x = 1;
static_assert(
    std::is_reference_v<decltype(returnRef(x))> // C++17
    // std::is_reference<decltype(returnRef(x))>::value // C++11
    ); // compilation failed
```

`returnRef` 返回 `T` 的引用类型，但是 `auto` 被推导为值类型，所以编译失败，这里需要使用 `decltype` 说明符：

```cpp
template<class T>
auto returnRef(T &t) -> decltype(t) {
    return t;
}

int x = 1;
static_assert(
    std::is_reference_v<decltype(returnRef(x))>
    );
```

### 3. 推导规则

`decltype(e)` 其中 e 的类型为 T。

1. 如果 e 是一个未加括号的标识符表达式（结构化绑定除外）或者未加括号的类成员访问，则 `decltype(e)` 推导出的类型是 e 的类型 T。如果不存在该类型，或 e 是一组重载函数，则无法进行推导。

2. 如果 e 是一个函数调用或者仿函数调用，则 `decltype(e)` 推导出的类型是其返回值的类型：

   ```cpp
   template<class T>
   auto returnRef(T &t) -> decltype(t) {
       return t;
   }
   
   int x = 1;
   auto &r = returnRef(x);
   static_assert(
       std::is_same_v<decltype(returnRef(x)), decltype(r)>
       );
   ```

3. 如果 e 是一个类型为 T 的左值，则 `decltype(e)` 是 `T &`：

   ```cpp
   int x = 1;
   int &rx = x;
   // decltype(rx) r = 1; compilation failed
   int y = 2;
   decltype(rx) ry = y;
   ```

4. 如果 e 是一个类型为 T 的将亡值，则 `decltype(e)` 是 `T &&`：

   ```cpp
   int x = 1;
   decltype(std::move(x)) y = std::move(x);
   static_assert(
       std::is_same_v<decltype(y), int &&>
       );
   ```

5. 如果 e 是一个类型为 T 的长度为 L 的数组类型，则 `decltype(e)` 是 `T [L]`：

   ```cpp
   int arr[] {1, 2, 3};
   decltype(arr) arr2 {1, 2, 3};
   // decltype(arr) arr3 {1, 2, 3, 4}; // compilation failed
   static_assert(std::is_same_v<decltype(arr), int[3]>
                 );
   ```

一些稍微复杂的例子：

```cpp
int i;
int *j;
int n[10];
decltype(i = 0) a = i; // int &
decltype(0, i) b = i;  // int &
decltype(i, 0) c = i;  // int
decltype(n[5]) d = i;  // int &
decltype(*j) e = i;    // int &
decltype(static_cast<int &&>(i)) f = 0; // int &&
decltype(i++) g = i; // int
decltype(++i) h = i; // int &
decltype("hello") k = "world"; // const char (&)[6]
```

### 4. 限定符推导

一般 `decltype(e)` 推导的类型会同步 e 的 cv 限定符：

```cpp
const int a = 1;
decltype(a) i = 2; // const int i = 2;
```

当 e 是未加括号的成员变量时，父对象表达式的 cv 限定符会被忽略：

```cpp
struct A {
    int x;
};

const A a = A();
decltype(a.x) i1 = 1;   // int i1 = 1;
decltype((a.x)) i2 = 1; // const int &i2 = 1;
```

### 5. decltype(auto)

C++14 标准允许 `decltype(auto)` 语句，以 `decltype` 的推导规则推导 `auto`，其**必须单独声明**，不能与指针、引用及 cv 限定符结合：

```cpp
decltype(auto) i = 1;       // int
decltype(auto) ri = (i);    // int &ri = i
int test() { return 0; }
decltype(auto) i2 = test(); // int i2 = test();
decltype(auto) i3 = {1, 2}; // compilation failed, {1, 2} not an expression

const int a = 1;
decltype(auto) b = a;    // const int b = a;
decltype(auto) ra = (a); // const int &ra = a;
```

使用此特性优化实现返回引用的模板：

```cpp
template<class T>
decltype(auto) returnRef(T &t) {
    return t;
}

int x = 1;
static_assert(
    std::is_reference_v<decltype(returnRef(x))>
    );
```

#### 5.1 decltype(auto) 作为非类型模板形参占位符

C++17 标准允许 `decltype(auto)` 作为非类型模板形参的占位符：

```cpp
template<decltype(auto) N>
void foo() {
    std::cout << N << std::endl;
}

int main() {
    static const int x = 1;
    static int y = 2;
    foo<x>();   // const int
    foo<(x)>(); // const int &
    foo<y>();   // compilation failed, y is not const
    foo<(y)>(); // int &
}
```

非类型模板参数需要在编译时确定。
