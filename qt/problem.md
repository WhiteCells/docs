### 常见错误

> 在以前的C++版本中，可以在类中为 static const 数据成员提供一个非整数类型（例如double）的初始值。但在C++11中，这种初始值必须被标记为`constexpr`，这是因为它需要在编译时就能被确定下来

```cpp
class A {
    static const int a = 1.1; // compilation failed
    static constexpr int b = 1.1;
    static const int c = 1;
};
```

函数声明中使用默认参数，函数实现不需要默认参数

```cpp
// Widget.h
class Widget : public QWidget {
public:
    // ...
    void init(QWidget *w = nullptr);
}
```

```cpp
// Widget.cpp
void Widget::init(QWidget *w) {
    // ...
}
```

继承时需注意是否指明限定符，不指定默认为 `private`

头文件记得防止重复包含：

```cpp
#ifndef _XXX_H_
#define _XXX_H_

#endif
```

main 函数

`CMakeLists.txt` 文件中的 `${}` 中检查单词拼写

当出现实现函数中类的已声明变量显示为未定义时则实现函数未添加作用域。未添加作用域，编译器会认为该函数实现是一个全局函数而不是一个类成员函数。
