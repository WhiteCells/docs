### 下载源代码

[chenshuo/muduo](https://github.com/chenshuo/muduo)

```sh
git clone git@github.com:chenshuo/muduo.git
```

### 编译

```sh
cmake -B ./build
cmake --build ./build
```

### 设置头文件与库文件位置

```sh
mv ./muduo/ /usr/local/include
mv ./build/lib/* /usr/local/lib
```

