### SDK（Software Development Kit）

https://go.dev/

https://studygolang.com/pkgdoc

https://pkg.go.dev/std



### Linux 配置 go 环境

```sh
wget https://go.dev/dl/go1.23.2.linux-amd64.tar.gz # 1.23.2

sudo tar -C /usr/local -xzf go1.23.2.linux-amd64.tar.gz
```

编辑 `~/.profile` 文件，添加以下内容：

```sh
export PATH=$PATH:/usr/local/go/bin
```

使更改生效：

```sh
source ~/.profile
```



### Windows 配置 go 环境

https://go.dev/dl/

将 `bin` 文件夹添加到系统 `PATH`

### go env

```sh
GO111MODULE='' # 控制模块支持的使用方式。空值表示使用默认行为：从 Go 1.16 开始，模块模式始终启用。
GOARCH='amd64' # 当前 Go 编译器目标架构。
GOBIN='' # 指定 Go 安装命令的目录
GOCACHE='/home/cells/.cache/go-build' # 编译时的缓存目录
GOENV='/home/cells/.config/go/env' # 存储 Go 环境变量的文件路径
GOEXE='' # 可执行文件的后缀名
GOEXPERIMENT='' # 表示是否启用 Go 的实验性功能
GOFLAGS='' # 默认传递给 go 命令的额外参数
GOHOSTARCH='amd64' # 当前 Go 编译器运行的宿主架构
GOHOSTOS='linux' # 当前 Go 编译器运行的宿主操作系统
GOINSECURE='' # 指定不安全的模块源，用于跳过验证
GOMODCACHE='/home/cells/go/pkg/mod' # 模块缓存目录
GONOPROXY='' # 不通过代理获取的模块路径列表
GONOSUMDB='' # 跳过校验和数据库验证的模块路径
GOOS='linux' # 当前 Go 编译器目标操作系统
GOPATH='/home/cells/go' # 工作区路径，存放 Go 项目、依赖和编译结果的目录
GOPRIVATE='' # 指定私有模块的路径前缀，不向 GOSUMDB 提交这些模块的信息
GOPROXY='https://goproxy.io,direct' # Go 模块代理设置
GOROOT='/usr/lib/go' # Go 工具链的安装路径
GOSUMDB='sum.golang.org' # 模块校验和数据库，用于验证模块的完整性
GOTMPDIR='' # Go 的临时文件目录
GOTOOLCHAIN='auto' # 指定工具链的使用策略
GOTOOLDIR='/usr/lib/go/pkg/tool/linux_amd64' # Go 工具链的二进制文件目录
GOVCS='' # 指定模块版本控制系统的使用策略
GOVERSION='go1.23.1' # 当前 Go 的版本号
GODEBUG='' # 用于启用 Go 调试选项，留空表示关闭调试
GOTELEMETRY='local' # 控制 Go 工具的遥测级别
GOTELEMETRYDIR='/home/cells/.config/go/telemetry' # 存储遥测数据的本地目录路径
GCCGO='gccgo' # 指定 gccgo 编译器的路径
GOAMD64='v1' # 指定 AMD64 的性能优化级别
AR='ar' # 指定用于静态库链接的工具
CC='gcc' # C 编译器的路径
CXX='g++' # C++ 编译器的路径
CGO_ENABLED='1' # 是否启用 CGO（调用 C 代码的功能）
GOMOD='/dev/null' # 当前活动模块文件路径，/dev/null 表示未启用模块模式
GOWORK='' # 当前活动的工作区文件路径，留空表示未设置
CGO_CFLAGS='-O2 -g' # 传递给 C 编译器的标志，-O2 -g 表示优化和调试信息
CGO_CPPFLAGS='' # 传递给 C++ 编译器的预处理标志，通常为空
CGO_CXXFLAGS='-O2 -g' # 传递给 C++ 编译器的标志
CGO_FFLAGS='-O2 -g' # 传递给 Fortran 编译器的标志
CGO_LDFLAGS='-O2 -g' # 传递给链接器的标志
PKG_CONFIG='pkg-config' # 指定 pkg-config 工具的路径
GOGCCFLAGS='-fPIC -m64 -pthread -Wl,--no-gc-sections -fmessage-length=0 -ffile-prefix-map=/tmp/go-build4213915858=/tmp/go-build -gno-record-gcc-switches' # 用于 CGO 的 C 编译器标志，由 Go 自动设置
```

