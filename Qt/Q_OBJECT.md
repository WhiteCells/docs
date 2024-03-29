### Q_OBJECT

`Q_OBJECT` 宏是 Qt 框架中的核心功能，只能用于继承自 `QObject` 的类。这个宏启用了类的几个重要的功能：

1. **信号与槽机制**：支持 Qt 的信号和槽机制，是 Qt 事件通信的基础。对象可以发出信号，并通过槽来响应这些信号
2. **运行时类型信息**：提供了对象的运行时类型信息(meta-information)。可以通过 `metaObject()` 方法访问类的信息，如类名、父类名、属性、方法等
3. **动态属性系统**：允许在运行时给对象添加自定义的属性。这些属性不需要在编译时定义在类中，可以灵活地添加和处理
4. **元对象编译器 (Meta-Object Compiler, moc)**：`Q_OBJECT` 宏还有关联的元对象编译器，moc会读取标记有这个宏的头文件，生成一份实现该类元信息的源代码
5. **Qt 属性系统**：此宏使类可以使用 `Q_PROPERTY` 宏来定义属性，这些属性可以在执行时被查询、读取、写入，并且可以通过设计器来改变
6. **枚举系统**：允许使用 `Q_ENUMS` 或 `Q_ENUM` 宏来声明枚举类型。这些枚举类型随后可以通过 Qt 的元对象系统进行使用
7. **本地化支持**：允许使用 `tr()` 方法对字符串进行本地化，方便在不同语言环境下的翻译工作
8. **信号与槽的自动连接**：通过在对象名称和槽函数名之间的对应关系，能够在 UI 文件加载时自动连接信号和槽
9. **对象树和父子关系**：支持创建一个对象树，当父对象删除时，所有子对象也会自动删除，有助于管理内存
10. **事件处理**：允许重写 `event()`、`timerEvent()`、`keyPressEvent()` 等事件处理函数来响应相应的事件

