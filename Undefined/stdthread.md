```cmd
PS C:\Users\L> g++ --version
g++.exe (x86_64-win32-seh-rev0, Built by MinGW-W64 project) 8.1.0
Copyright (C) 2018 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

g++ 版本低导致无法使用 `std::thread`

下载新版本 [github-mingw-builds-binaries/releases](https://github.com/niXman/mingw-builds-binaries/releases)

指定编译器使用的 C++ 标准 `-std=c++11`

遇到 `std::cout` 调试出错，我的错误在根目录下 `libstdc++-6.dll` 没有替换，解决方法直接删除 system32 目录下的这个文件，让编译要找的文件直接到环境变量中去找。