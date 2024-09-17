### Item05: Prefer auto to explicit type declarations (优先考虑使用 auto 而非显式类型声明)

`auto` 变量从初始化表达式中推导出类型，所以必须初始化：

```cpp
int x1;      // 潜在的未初始化的变量

auto x2;     // 错误! 必须初始化

auto x3 = 0; // 正确
```

因为 `auto` 使用 Item2 所描述的 `auto` 类型推导技术，它甚至能表示一些只有编译器才知道的类型：

```cpp
auto dereFuPLess = [](const std::unique_ptr<Widget> &p1, 
                      const std::unique_ptr<Widget> &p2) 
{
    return *p1 < *p2;
};
```

使用 C++14，在 lambda 表达式中的形参可以使用 `auto`：

```cpp
auto dereFuPLess = [](const auto &p1, const auto &p2) {
    return *p1 < *p2;
}
```

可以使用 `std::function` 对象，`std::function` 对象是 C++11 标准模板库中的一个模板，它泛化了函数指针的概念。与函数指针只能指向函数不同，`std::function` 可以指向任何可调用对象。当声明函数指针时必须指向函数类型（函数签名），同样创建 `std::function` 对象时也需要提供函数签名，由于它是一个模板所以在它的模板参数里提供。

假设想声明一个 `std::function` 对象 func 使它指向一个可调用对象，比如一个具有这样函数签名的函数：

```cpp
bool(const std::unique_ptr<Widget> &p1, const std::unique_ptr<Widget> &p2);
```

就要这么写：

```cpp
std::function<bool(const std::unique_ptr<Widget> &p1,
                   const std::unique_ptr<Widget> &p2)> func;
```

因为 lambda 表达式能产生一个可调用对象，所以现在可以将闭包放到 `std::function` 对象中。这意味着可以不使用 `auto` 写出 C++11 版的 `dereUPLess`：

```cpp
std::function<bool(const std::unique_ptr<Widget> &p1, 
                   const std::unique_ptr<Widget> &p2)> func = [] (const std::unique_ptr<Widget> &p1, 
                                                                  const std::unique_ptr<Widget> &p2) { 
    return *p1 < *p2; 
};
```

语法冗长，重复写了很多类型参数，使用 `auto` 声明的变量保存一个闭包这个变量将会得到和闭包一样的类型。

实例化 `std::function` 并声明一个对象，这个对象将会有固定大小。当使用这个对象保存一个闭包时它可能大小不足不能存储，这个时候 `std::function` 的构造函数将会在堆上面分配内存来存储，这就造成了使用 `std::function` 比 `auto` 会消耗更多的内存。 并且通过 `std::function` 调用一个闭包几乎无疑比 `auto` 声明的对象调用要慢。

使用 `auto` 除了使用未初始化的无效变量，省略冗长的声明类型，直接保存闭包外，它还可以避免依赖类型快捷方式的问题：

```cpp
std::vector<int> v;
unsigned sz = v.size();
```

`v.size()` 的标准返回类型是 `std::vector<int>::size_type`，很多人知道 `std::vector<int>::size_type` 实际上被指定为无符号类型，所以很多人认为使用 `unsigned` 比写标准返回类型方便，这就会造成一些问题，如在 Windows 32-bit 上 `std::vector<int>::size_type` 和 `unsigned int` 都是一样的类型，但是在 WIndows 64-bit 上 `std::vector<int>::size_type` 是 64 位，`unsigned int` 是 32 位，所以这段代码在 Windows 32-bit 上正常工作，但是当把程序移植到 Windows 64-bit 上就可能出现问题。

可以使用 `auto` 来确保不浪费时间去处理这些细枝末节：

```cpp
auto sz = v.size();
```

使用 `auto` 是一个明智的选择，观察下面未使用 `auto` 的代码：

```cpp
std::unordered_map<std::string, int> m;

for (const std::pair<std::string, int> &p : m) {
    
}
```

看起来合情合理的表达，但是这里有一个问题，`std::unordered_map` 的 `key` 是一个常量，所以 `std::pair` 的类型不是 `std::pair<std::string, int>` 而是 `std::pair<const std::string, int>`。编译器会努力的找到一个方法把前者转换为后者，编译器会创建一个对象，这个对象的类型是 p 想绑定到的对象的类型，即 m 中元素的类型，然后将 p 的引用绑定到这个临时对象上，这个循环迭代结束时，临时对象会被销毁。如果是这样的一个循环，你可能会对它的一些行为感到疑惑，因为你确信 p 是 m 中的各个元素的引用。

可以使用 `auto` 来避免这些很难意识到的类型不匹配的错误：

```cpp
for (const auto &p : m) {
    
}
```

这样的代码无疑更效率，且更容易编写，如果你把 p 换成指向 m 的各个元素的指针，在没有 `auto` 版本中 p 会指向一个临时变量，这个临时变量在每次迭代完成时被销毁。

后面两个例子说明了显示的指定类型可能会导致不想看到的类型转换，如果使用 `auto` 声明目标变量就不用担心这个问题。然而 `auto` 也不是完美的，每个 `auto` 变量都从初始化表达式中推导类型，有些表达式的类型与我们期望的不同。

当你关心使用 `auto` 代替传统类型声明对源码可读性有影响，`auto` 是可选的，不是命令，在某些情况下，如果你的专业判断告诉你使用显示类型声明比 `auto` 要更清晰且更容易维护，那就不必再坚持使用 `auto`。牢记 C++ 没有在其他众所周知的语言所用的类型接口上开辟新领域。

一些开发者也担⼼使⽤ `auto` 就不能瞥一眼源代码便知道对象的类型，然而，IDE 扛起了部分担子，在很多情况下，少量显示一个对象的类型对于知道对象的确切类型是有帮助的，这通常已经足够了。举个例子，要想知道一个对象是容器还是计数器还是智能指针，不需要知道它的确切类型，一个适当的变量名称就能告诉我们大量的抽象类型信息。

> 使用 `auto` 允许编译器自动推断变量的类型，这在代码编写中有几个优势，但也带来了一些担忧。这里重点解释了这种担忧并提供了一种观点：
>
> 1. **代码可读性**：一些开发者担心使用 `auto`会降低代码的可读性，因为仅通过查看代码无法直接知道变量的确切类型。在传统的编码实践中，明确的类型声明被视为有助于理解代码的工作方式。
>
> 2. **IDE和工具的作用**：然而，如今的集成开发环境（IDE）和其他代码编辑工具已经非常智能，能够很容易地显示变量的实际类型，即使它们是通过 `auto` 声明的。这意味着开发者可以通过悬停指针或使用其他辅助功能快速获得类型信息，而不必在源代码中显式写出。
>
> 3. **变量命名的重要性**：作者强调，即便没有具体的类型声明，一个好的、描述性的变量名也能提供大量信息。例如，如果变量名为 `user_list`，那么不管其具体类型如何（例如，它可能是一个 `vector` 或其他容器类型），该名字已经表明了这是一种容纳“用户”的容器。同样地，`smart_ptr` 这样的变量名表示该对象是一种智能指针，即使我们不知道它是`std::shared_ptr`、`std::unique_ptr`还是其他类型。
>
> 4. **代码的抽象层次**：使用 `auto` 和描述性的变量名可以帮助提高代码的抽象层次，使开发者更专注于变量的“角色”，而不是它们的具体类型。这有助于理解代码的逻辑结构和设计意图。
>
> 虽然使用 `auto` 可能会隐藏一些类型信息，但通过现代工具和良好的命名惯例，它可以提高代码的整洁性和抽象程度，同时减少因类型声明引起的复杂性和编码错误。在现代C++实践中，这种平衡被视为有益的。

 如果初始化表达式改变，变量的类型也会改变，这意味着使用 `auto` 可以完成一些重构工作，假如一个函数返回类型被声明为 `int`，但是后来认为声明为 `long` 更好，调用它作为表达式的变量会自动改变类型，但是如果不使用 `auto` 就需要在源代码中挨个找到调用地点然后修改它们。

记住：

- `auto` 变量必须初始化，通常它可以避免一些移植性和效率性的问题，也使得重构更方便，还能少打几个字。
- 正如 Item2 和 Item6 讨论的，`auto` 类型的变量可能会踩到一些陷阱。

