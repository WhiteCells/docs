### QWidget default construct

```cpp
QWidget(Qwidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags())
```

QWidget 是所有 Qt GUI 界面类的基类，Qwidget 是 QObject 的子类，QWidget 不是抽象类，可以实例化。

通过传入 Qwidget 构造函数的参数或对象调用`setParent()` 和 `setWindowFlags()` 指定父窗口部件和窗口部件的标识。

```cpp
QWidget *widget = new QWidget(nullptr, Qt::Window | Qt::WindowCloseButtonHint);
// or
QWidget *widget = new QWidget();
widget->setParent(nullptr);
widget->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
```

### QWidget window flags

window flags 为 `WindowType` 枚举类型

```cpp
enum WindowType {
    
    // QWidget 构造函数的默认值
    // 如果没有父窗口，则是一个独立窗口
    // 否则是一个子窗口部件
    Widget = 0x00000000,
    
    // 无论是否有父窗口，新窗口部件是一个窗口
    // 窗口边框和标题栏
    Window = 0x00000001,
    
    // QDialog 构造函数的默认值
    // 新窗口部件是对话框
    Dialog = 0x00000002 | Window,
    
    // Macintosh 表单
    Sheet = 0x00000004 | Window,
    
    // Macintosh 抽屉
    Drawer = Sheet | Dialog,

    // 弹出式顶部窗口
    Popup = 0x00000008 | Window,
    
    // 工具窗口，显示工具按钮的小窗口
    // 如果有父窗口，则显示在父窗口部件上
    // 否则相当于使用 Qt::WindowStaysOnTopHint
    Tool = Popup | Dialog,
    
    // 提示窗口
    ToolTip = Popup | Sheet,
    
    // QSplashScreen 构造函数默认值
    // 欢迎窗口
    SplashScreen = ToolTip | Dialog,
    
    // QDesktopWidget 构造函数默认值
    // 桌面
    Desktop = 0x00000010 | Window,
    
    // 子窗口
    // 无论该窗口部件是否有父窗口部件
    SubWindow = 0x00000012,
    
    // 
    ForeignWindow = 0x00000020 | Window,
    
    // 
    CoverWindow = 0x00000040 | Window,
    
    // 用于提取窗口标识中的窗口类型部分的掩码
    WindowType_Mask = 0x000000ff,
    
    // 为 Windows 系统上的窗口装饰一个窄的对话框边框
    MSWindowsFixedSizeDialogHint = 0x00000100,
    
    // 为 Windows 系统上的窗口添加自身的显示上下文菜单（display context）
    MSWindowsOwnDC = 0x00000200,
    BypassWindowManagerHint = 0x00000400,
    
    // 完全忽视窗口管理器，产生一个不被管理的无窗口边框的窗口
    // 此时用户无法使用键盘输入，除非手动调用 activeWindow()
    X11BypassWindowManagerHint = BypassWindowManagerHint,
    
    // 无窗口边框的窗口
    // 无法移动和改变窗口大小
    FramelessWindowHint = 0x00000800,
    
    // 为窗口装饰一个标题栏
    WindowTitleHint = 0x00001000,
    
    // 为窗口添加一个窗口系统菜单，尽可能添加一个关闭按钮
    WindowSystemMenuHint = 0x00002000,
    
    // 为窗口添加一个 '最小化' 按钮
    WindowMinimizeButtonHint = 0x00004000,
    
    // 为窗口添加一个 '最大化' 按钮
    WindowMaximizeButtonHint = 0x00008000,
    
    // 为窗口添加 '最小化' '最大化' 按钮
    WindowMinMaxButtonsHint = WindowMinimizeButtonHint | WindowMaximizeButtonHint,
    
    // 为窗口添加一个 '上下文帮助' 按钮
    WindowContextHelpButtonHint = 0x00010000,
    WindowShadeButtonHint = 0x00020000,
    
    // 告知窗口系统，停留所有窗口的上面
    WindowStaysOnTopHint = 0x00040000,
    WindowTransparentForInput = 0x00080000,
    WindowOverridesSystemGestures = 0x00100000,
    WindowDoesNotAcceptFocus = 0x00200000,
    MaximizeUsingFullscreenGeometryHint = 0x00400000,

    // 关闭默认的窗口标题提示
    CustomizeWindowHint = 0x02000000,
    WindowStaysOnBottomHint = 0x04000000,
    WindowCloseButtonHint = 0x08000000,
    MacWindowToolBarButtonHint = 0x10000000,
    BypassGraphicsProxyWidget = 0x20000000,
    NoDropShadowWindowHint = 0x40000000,
    WindowFullscreenButtonHint = 0x80000000
};
```

### Case

```cpp
#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Qt::WindowFlags flags = Qt::Window | Qt::WindowContextHelpButtonHint | Qt::WindowCloseButtonHint;
    // widget = new QWidget(nullptr, flags);
    QWidget *widget = new QWidget();
    flags |= Qt::WindowMinimizeButtonHint;
    flags &= ~Qt::WindowMinimizeButtonHint;
    // flags |= Qt::WindowType_Mask;
    widget->setWindowFlags(flags);
    widget->resize(200, 200);
    widget->show();
    return a.exec();
}
```

