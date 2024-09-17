### Window 平台 Qt 环境

[Qt Downloads](https://download.qt.io)

选择组件时在选择的版本号中选择 MinGW 或 MSVC 编译器，如需在 vs 中运行 Qt 时需选择 MSVC

### Linux 平台 Qt 环境

```sh
# qt6
yay -S qt6-base
yay -S qt6-multimedia
yay -S qt6-tools
```

### Visual Studio Code

安装插件 `Qt Tools` 便于编辑 **.ui** 文件

在 Window10 平台发现以下问题（Linux 正常）：

代码中包含 `qDebug` 语句将导致程序无法运行

> 解决方法：修改 CMake 工具包为 Qt GCC 编译器，需配置 Qt 环境变量 `C:\Qt\Tools\mingw1120_64\bin`、`C:\Qt\6.6.1\mingw_64\bin`

程序正常运行，vscode 终端不打印 `qDebug` 信息问题

> 解决方法：修改 CMakeLists.txt 文件
>
> ```cmake
> # 使用的是 Qt Creator 生成的 CMakeLists.txt 文件
> set_target_properties(geometry-case PROPERTIES
>        ${BUNDLE_ID_OPTION}
>        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
>        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
>        MACOSX_BUNDLE TRUE
>        # WIN32_EXECUTABLE TRUE # 值修改为 OFF
>        WIN32_EXECUTABLE OFF
> )
> ```

### Visual Studio

安装 `Qt Visual Studio Tools` 插件

设置插件 `拓展->Qt VS Tools->Options->Versions` 中添加 Qt MSVC `C:\Qt\6.6.1\msvc2019_64\bin\qmake.exe`

项目配置 `C++ 语言标准` 为 `ISO C++17 标准`

ui 文件闪退问题，设置插件 `拓展->Qt VS Tools->Options->General` 中 `Qt Designer` 下 `Run in detached window` 修改为 `true` 

无法打印 `qDebug` 信息，设置项目属性，修改 `链接器 -> 系统 -> 子系统` 选为控制台

### Qt Creator

Qt Creator 无法打印 `qDebug` 信息时，`项目 -> 运行 -> 在终端中运行`

### Qt6 CMakeLists

```cmake
cmake_minimum_required(VERSION 3.5)

project(QPLAINTEXTEDIT VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    main_window.cpp
    main_window.h
)

qt_add_executable(painter
    ${PROJECT_SOURCES}
)

target_link_libraries(painter PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)
```

### 添加 .ui 文件

例如添加 `login.ui`，**.ui** 文件内的对象名称为 `LoginDialog`。

```cpp
// .h
QT_BEGIN_NAMEPSACE
namespace Ui { // 必须是 Ui 
class LoginDialog; // ClassName 为 ui 文件中对象的名称
}
QT_END_NAMESPACE
    
class Widget : public QWidget {
    Q_OBJECT
private:
    Ui::LoginDialog *ui_;
}
```

```cpp
// .cpp
#include "ui_login.h" // ui_ 前缀加上 .ui 文件名

LoginDialog::LoginDialog(QWidget *parent = nullptr) : 
    ui(new Ui::LoginDialog) { // 初始化 ui
    
    ui->setupUi(this);
}
```

```cmake
# CMakeLists.txt
qt_add_executable(app ${PROJECT_SOURCES} login.ui)
```

```xml
<?xml version="1.0" encoding="UTF-8"?>
<ui version="4.0">
 <class>Dialog</class>
 <widget class="QDialog" name="Dialog">
 </widget>
 <resources/>
 <connections/>
</ui>
```

### 添加 .qrc 文件

```sh
# tree
├── resource
│   ├── ico
│   │   └── avator.png
│   └── qss
│       └── style.qss
└── resource.qrc
```

```cmake
# CMakeLists.txt
qt_add_executable(app ${PROJECT_SOURCES} resource.qrc)
```

```xml
<!-- resource.qrc -->
<RCC>
    <qresource prefix="/ICO">
        <file>/ico/avator.png</file>
    </qresource>
    <qresource prefix="/QSS">
        <file alias="style">/qss/style.qss</file>
    </qresource>
</RCC>
```

使用资源文件：`":/ICO/ico/avator.png"` `:/QSS/style`
