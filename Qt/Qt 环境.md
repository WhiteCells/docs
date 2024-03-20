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

安装插件 `Qt Tools` 便于编辑 ui 文件

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

无法打印 `qDebug` 信息，设置项目属性，修改 `链接器->系统->子系统` 为控制台

