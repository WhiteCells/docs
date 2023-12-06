报错

```cmd
ERROR: Unable to start debugging. GDB exited unexpectedly.或者Unexpected GDB output from command “-exec-run“
```

bin 目录 用户环境变量

D:\mingw64\bin\libstdc++-6.dll

将`D:\setup\msys64\mingw64\bin`下的`libstdc++-6.dll`复制到`C:\Windows\System32`下，就可以编译C++



libstdc++-6.dll的问题。很可能你安装了qt或其它版本的MinGW又或者其它什么东西，总之，你另外安装的这个东西中也有一个libstdc++-6.dll扩展文件，这个文件和你所使用的c++编译器安装目录下的扩展文件重名（例如我的D:\setup\msys64\mingw64\bin\libstdc++-6.dll）。这使得VSCode在编译c++工程文件时找到了错误的libstdc++-6.dll扩展（或者是它找到了多个，不知道用哪一个），出现了ERROR: Unable to start debugging. GDB exited unexpectedly.报错。

    将D:\setup\msys64\mingw64\bin下的libstdc++-6.dll复制到工程目录下，再次运行C++代码，如果还出现相同的报错，那说明不是扩展文件的问题，你此时可以去其他地方找solution了。
    对于每一个工程，将扩展文件复制到工程目录下的做法不太优雅。为了更优雅地编译C++工程，你可以在用户环境变量中将D:\setup\msys64\mingw64\bin移至最上方，使得VSCode可以先找到这个目录下的libstdc++-6.dll扩展，这在某些情况下可以解决问题，有时却不能。
对于每一个工程，将扩展文件复制到工程目录下的做法不太优雅。为了更优雅地编译C++工程，你可以在用户环境变量中将D:\setup\msys64\mingw64\bin移至最上方，使得VSCode可以先找到这个目录下的libstdc++-6.dll扩展，这在某些情况下可以解决问题，有时却不能。
