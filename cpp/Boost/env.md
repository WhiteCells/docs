### Windows

https://www.boost.org/users/download/

使用 MinGW

```cmd
.\bootstrap.bat gcc
.\b2.exe toolset=gcc install --prefix="D:\dev\env\boost"
```

### Linux

使用包管理器

```sh
sudo apt install libboost-all-dev
paru -S boost
```

源码编译安装

https://www.boost.org/users/download/

```sh
tar -xvzf boost_<version>.tar.gz
cd boost_<version>
```

运行 `bootstrap.sh`

```sh
./bootstrap.sh
```

编译安装

```sh
./b2 install --prefix=$HOME/.local/boost
```

