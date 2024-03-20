### Qt 6 CMakeLists

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

