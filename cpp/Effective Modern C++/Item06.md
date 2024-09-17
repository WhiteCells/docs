### Item06: Use the explicitly typed initializer idiom when auto deduces undesired types (auto 推导若非己愿，使用显式类型初始化惯用法)

 `auto` 不是完美的。举个例子：

```cpp
std::vector<bool> features(const Widget &w);
bool highPriority = features(w)[5];
processWidget(w, highPriority);
```

如果使用 `auto` 来代替显示指定类型：

```cpp
auto highPriority = features(w)[5];
processWidget(w, highPriority); // 未定义行为
```

使用 `auto` 后 `highPriority` 不再是 `bool` 类型，从概念上 `std::vector<bool>` 存放 `bool`，但是 `std::vector<bool>` 的 `operator[]` 不会返回容器中元素的引用，而是返回一个 `std::vector<bool>::reference` 的对象（嵌套于 `std::vector<bool>` 中的类），
