

```sh
go build xxx.go
go build -o xxx xxx.go

go run xxx.go

gofmt -w xxx.go
```

不能定义未使用的变量或包。

函数左花括号不能换行。

```go
package mylib1

import "fmt"

// 导出函数，可以从其他包访问
func Print1() {
    fmt.Println("This is Print1")
}

// 未导出函数，只能在当前包中使用
func print2() {
    fmt.Println("This is print2")
}
```

强类型语言。

### 数据类型

- 基本数据类型
  - 数值类型
    - 整形类型：int，int8，int16，int32，int64，uint，uint8，uint16，uint32，uint64，byte
    - 浮点类型：float32，float64
  - 字符类型
  - 布尔类型
  - 字符串类型
- 派生数据类型
  - 指针
  - 数组
  - 结构体
  - 通道
  - 函数
  - 切片
  - 接口
  - map

Go 主要包含三个目录：`src`、`pkg`、`bin` 三个目录

```sh
go mod init project

go run main.go

go build -o ./bin .
./bin/project
```



### package 包机制

源码文件必须属于某个包，同**一个文件夹下的所有 `.go` 文件都要属于一个包**。

`main` 是一个特殊的包名，可执行程序的入口 `main` 函数**必须**位于 `main` 包，其余自定义的包名**约定**与所处文件夹名相同。

导入包使用 `import` 关键字，参数是包的文件夹路径，具体调用内容时使用的才是包名。

### init 函数

```go
package mylib1

import "fmt"

func init() {
	fmt.Println("mylib1 init")
}

func Print1() {
	fmt.Printf("print1\n")
}
```

`init()` 函数调用实际是当使用 `import` 语句引入包时，编译器就会安排在程序的 `main()` 函数之前执行。

一个包可以有多个 `init()` 函数，但是执行顺序是不确定的。

### Go Modules 模块

go1.13 推出模块化机制，`go.mod` 是模块工程描述文件，其中会声明当前工程名，以及依赖的其他模块信息。

如果工程依赖于开源库或框架，需要在 `go.mod` 中进行以来声明，开源模块可以在 https://pkg.go.dev/ 中查找。

添加依赖例子：

```sh
go get github.com/xxx/xxx@v1.0
```

拉去成功后会在 `go.mod` 中写入相关依赖信息，此外会生成一个 `go.sun` 文件，用于锁定依赖版本，拉取的源码在 `$GOPATH/pkg/mod` 目录下。

拉取超时时尝试设置 `GOPROXY` 环境变量：

```sh
go env -w GOPROXY=https://goproxy.io,direct
# or
go env -w GOPROXY=https://proxy.golang.com.cn,direct
```

企业内部开发时，可以将似有 git 地址加入 `GOPRIVATE` 环境变量：

```sh
go env -w GOPRIVATE=xxx.xxx.xxx.xxx
```

### 常量与变量

变量使用 `var` 关键字定义，数据类型在变量名后面：

```go
var i int = 1
```

支持自动类型推导，如果声明时直接赋值，可以省略数据类型。使用 `:=` 可以实现变量的声明和定义，此时可以省略 `var`：

```go
var ii = 1
i := 1
```

支持多个变量同时声明：

```go
var i, j, k int = 1, 2, 3
var ii, jj, kk = 1, "2", 3.3
var (
    i int
    j bool = false
    k string
)
```

常量使用 `const` 声明，声明时必须赋值：

```go
const i int = 1
const (
    i int    = 1
    j bool   = false
    k string = "test"
)
```

### 类型转换

使用 `T()` 进行转换，`T` 为类型名：

```go
i := 1
f := float32(i)
```

### 数据类型

go 语言数据类型分为两大类：值类型、引用类型。

基本类型：

```go
bool   // 默认 false
string // 默认 ""
int int8 int16 int32 int64 // 长度取决于 CPU 字长
uint uint8 uint16 uint32 uint64 uintptr // 长度取决于 CPU 字长
byte // uint8 别名
rune // int32 别名
float32 float64
complex64 complex128 // 复数类型
```

### 指针

```go
i := 1
var iPtr *int = &i // 声明指针并赋值
var j int = *iPtr  // 指针解引用
```

### type 关键字

为类型取别名：

```go
type DataLen int32
```

### 数组

定长数组：

```go
var arr [2]string
arr[0] = "test"
```

变长数组：

```go
var arr []string
arr = append(arr, "test")
arr = append(arr, "test1", "test2")

var arr2 []string{"test1", "test2"}

var arr3 = make([]string, 3)
```

变长数组组合和切分：

```go
arr = append(arr[:1], arr[2:]...)
```

变长数组拷贝：

```go
var arr = []string{"1", "2"}
var arr2 = make([]string, 2)
copy(arr2, arr)
```

### 字典

初始化 map：

```go
var m1 = make(map[string]string)

var m2 = make(map[string]string{"key1": "value1", "key2": "value2"})
```

添加键值对：

```go
m1["key1"] = "value1"
```

删除键值对：

```go
delete(m1, "key1")
```

以键获取值：

```go
print(m["key1"])
```

判断键是否存在：

```go
ele, exist := m["key1"]
print(ele, exist)
```

### 结构体

定义结构体：

```go
type Poto struct {
    X int
    Y int
}
```

结构体成员字段名称的首字母大小写决定其可见性：

首字母大写：共有成员

首字母小写：私有成员

初始化：

```go
var poto1 Poto = Poto{1, 2}

var poto2 = Poto{1, 2}

poto3 := Poto{1, 2}
```

初始化结构体并获取指针：

```go
var poto1 *Poto = new(Poto)
var poto2 *Poto = &Poto{}
var poto3 = new(Poto)
poto3 := new(Poto)
```

成员变量访问：

```go
print(poto.X, poto.Y)
```

即使是指针，也是使用 `.` 访问。

结构体函数：

```go
func (poto *Poto) foo() int {
    return poto.X + poto.Y
}
```

