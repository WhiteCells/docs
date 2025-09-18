### 1. 流

标准 I/O 库和文件 I/O 的区别：

- 标准 I/O 库处理很多细节，如缓冲区分片、以优化的块长度执行 I/O 等
- 文件 I/O 函数是围绕文件描述符进行
- 标准 I/O 库围绕流进行

#### 1.1 流的定向

ASCII 字符集中一个字符用一个字节表示，国际字符集中一个字符可以用多个字节表示，标准 I/O 文件流可用于单字节或多字节字符集，流的定向决定了所处理的字符是单字节还是多字节

当一个流最初创建时是没有定向

- 对未定向的流使用单字节 I/O 函数，则将该流的定向设置为字节定向的（处理单字节）
- 对未定向的流使用多字节 I/O 函数，则将该流的定向设置为宽定向的（处理多字节）

只有两个函数可以改变流的定向

```c
#include <stdio.h>

// 清除一个流的定向
FILE *freopen(const char *pathname, const char *mode, FILE *stream);

#include <wchar.h>

// 设置流的定向，不改变已定向流
int fwide(FILE *stream, int mode);
```

#### 1.2 三个标准流

操作系统对每个进程定义了 3 个流，这 3 个流可以自动被进程使用，定义在 `stdio.h` 中

1. 标准输入：预定义的文件指针（FILE 对象）为 `stdin`，内部的文件描述符是 `STDIN_FILENO`，占用文件描述符 0
2. 标准输出：预定义的文件指针（FILE 对象）为 `stdout`，内部的文件描述符是 `STDOUT_FILENO`，占用文件描述符 1
3. 标准错误：预定义的文件指针（FILE 对象）为 `stderr`，内部的文件描述符是 `STDERR_FILENO`，占用文件描述符 2

### 2. FILE 对象

使用 `fopen` 函数打开一个流时，返回一个指向 `FILE` 对象的指针，该对象是一个结构，包含了标准 I/O 库为管理该流所需要的信息：

- 用于实际 I/O 的文件描述符
- 指向用于该缓冲区的指针
- 该流缓冲区的长度
- 当前在缓冲区中的字符数
- 出错标志

`FILE` 对象包含了文件描述符，标准 I/O 函数可以看作对 fd 直接操作的系统调用的封装，优点是带有 I/O 缓冲，能减少系统调用的次数

![]()

### 3. 缓冲

标准 I/O 库提供缓冲是为了减少调用 `read` 和 `write` 的次数，标准 I/O 对每个 I/O 流自动的进行缓冲管理

#### 3.1 三种缓冲类型

标准 I/O 库提供了三种类型的缓冲：

1. **全缓冲**：当缓冲区满了（达到其容量上限）或者明确调用`fflush()`函数时，数据才会被写入文件或设备。这种模式在处理大量数据时效率最高，因为它可以最大限度地减少写入操作的次数。默认情况下，大多数流（如文件流）都是全缓冲的。
2. **行缓冲**：每次遇到一个换行符（'\n'）或者调用`fflush()`函数时或者缓冲区填满，缓冲区的内容会被写入文件或设备。此外，当程序从缓冲的输入流中读取数据时，也会触发写入操作。这种模式通常用于终端设备，因为用户通常希望每输入一行数据就能立即看到反馈。
3. **无缓冲**：每次调用输入或输出函数，数据都会立即被写入文件或设备，不经过缓冲区。这种模式通常用于一些不能容忍延迟的情况，比如日志记录或者错误消息的输出。

在一个流上执行第一次 I/O 操作时，相关标准 I/O 函数通常调用 malloc 获取使用的缓冲区

```c
#include <stdio.h>

// 设置流的缓冲类型
void setbuf(FILE *stream, char *buf);
    argument:
        - stream: 打开的文件对象的指针
        - buf: 指向缓冲区的指针，长度为 BUFSIZ 定义在 stdio.h

    return:
        - 成功返回 0
        - 失败返回非 0，设置 errno

void setbuffer(FILE *stream, char *buf, size_t size);
    argument:
        - size: 缓冲长度

void setlinebuf(FILE *stream);

int setvbuf(FILE *stream, char *buf, int mode, size_t size);
    argument:
        - mode: 指定缓冲区类型
            - _IOFBF: 全缓冲
            - _IOLBF: 行缓冲
            - _IONBF: 不带缓冲，此时忽略 buf 和 size 参数

note:
    - 在一个函数内分配自动类型（栈）的标准 I/O 缓冲区
      为了防止内存泄漏，从该函数返回之前必须关闭流
    - 某些操作系统默认缓冲区的一部分存放自己的管理操作信息，
      可以存放在缓冲区的实际字节将少于 size
    - 通常使用系统自动选择缓冲区大小并自动分配缓冲区，
      这种情况下关闭流，标准 I/O 库会自动释放缓冲区
```

#### 3.2 缓冲区冲洗

冲洗是负责数据传到内核，不是立即写到磁盘文件

缓冲区可以由标准 I/O 操作自动冲洗，也可以手动调用函数 `fflush` 冲洗一个流

```c
#include <stdio.h>

int fflush(FILE *stream);
    argument:
        - stream: 打开文件对象的指针

    return: 
        - 成功返回 0
        - 失败返回 EOF
```

冲洗是双向的：

输出流 => 内核 => 磁盘或终端

输出流 => 用户缓冲区

冲洗（flush）操作是双向的。在标准 I/O 库中，缓冲区分为输入缓冲区和输出缓冲区，而冲洗操作可以将缓冲区中的数据刷新（写入或者读取）到相应的设备或者文件中。

具体来说，对于输出流，当执行`fflush`函数或者标准I/O库自动冲洗时，输出缓冲区的数据会被刷新到内核的输出缓冲区中，然后再通过系统调用`write()`函数将数据写入磁盘或者终端。而对于输入流，当执行`fflush`函数或者从标准I/O库中读取数据时，输入缓冲区中的数据会被刷新到用户自定义的输入缓冲区中，然后供程序读取。

需要注意的是，输入流的冲洗操作并不是很常见，因为一般情况下输入流的数据已经被读取到了程序的变量中，不需要再进行冲洗。输出流的冲洗操作则比较常见，例如在程序结束前需要确保所有的输出数据都已经写入到文件中，就可以使用`fflush`函数来强制刷新输出缓冲区。

#### 3.3 标准流与缓冲

标准输入和输出，默认情况指向终端设备的流是行缓冲；标准错误，默认情况不带缓冲，不会是全缓冲

### 4. 打开流

```c
#include <stdio.h>

// 打开一个指定的文件
FILE *fopen(const char *pathname, const char *mode);
    argument:
        - pathname: 文件路径
        - mode: 指定对 I/O 流的读写方式，字符串的形式
                b 是区分二进制文件和文本文件，Unix 内核不区分
            - r 或 rb: 为读打开
            - w 或 wb: 将文件截断至 0，或为写而创建
            - a 或 ab: 为在文件写而打开或创建
            - r+ 或 r+b 或 rb+: 为读和写打开
            - w+ 或 w+b 或 wb+: 将文件截断至 0，或为读和写而打开或创建
            - a+ 或 a+b 或 ab+: 为在文件末读和写而打开或创建
    return:
        - 成功返回文件指针
        - 失败返回 NULL

// 将文件描述符包装成一个标准 I/O 流
// 某些特殊类型的文件（管道、socket等）不能用 fopen 打开，必须获取 fd，然后 fdopen
FILE *fdopen(int fd, const char *mode);

// 在指定的流上打开指定文件
FILE *freopen(const char *pathname, const char *mode, FILE *stream);
    argument:
        - stream: 指定的流，若 fd 已经打开，则先关闭该流，
                  若已指向，则清除指向
```

当以读和写方式打开一个文件时（带 +），会有限制：

1. 如果写操作后没有 `fflush`（冲洗缓冲区）、`fseek`、`fsetpos`、`rewind` 操作之一，则写操作之后不能紧跟读操作，文件指针仍然停留在写操作后的位置，同时数据也可能没有写入文件
2. 如果读操作后面没有 `fseek`、`fsetpos`、`rewind`操作之一，文件指针在文件开头，则读操作后面不能紧跟写操作

当以读和写模式（`mode`中带`+`号的类型）打开一个文件时，需要注意以下几点：

1. **文件指针：** 文件指针用于跟踪当前的读/写位置。在读或写数据后，文件指针会自动移动到读取或写入的数据的末尾。如果需要在不同的位置进行读取或写入操作，使用`fseek`，`fsetpos`或`rewind`等函数调整文件指针的位置。

2. **写后读：** 如果在写操作后立即进行读操作，而没有使用`fseek`，`fsetpos`，`rewind`或`fflush`等函数调整文件指针的位置，那么你将从写入数据的末尾开始读取，可能并不是你期望的结果。这是因为写操作会移动文件指针到写入数据的末尾。

3. **读后写：** 类似地，如果在读操作后立即进行写操作，而没有使用`fseek`，`fsetpos`，`rewind`或`fflush`等函数调整文件指针的位置，那么将在读取数据的末尾开始写入，可能会覆盖原有的数据。

4. **缓冲区：** 当你写入数据时，数据可能首先被写入缓冲区，而不是直接写入文件。可以使用`fflush`函数强制将缓冲区的数据写入文件。

5. **文件打开模式：** 你选择的文件打开模式（`r+`，`w+`，`a+`等）会影响到你可以在哪里进行读写操作，以及文件会如何被处理。例如，`w+`模式会首先清空文件，而`a+`模式则会将文件指针移动到文件的末尾，使得所有的写操作都在文件的末尾进行。

```c
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    FILE *fptr = fopen("test.txt", "w+");
    if (NULL == fptr) {
        perror("fopen");
        return 0;
    }
    for (int i = 1; i < 10; ++i) {
        char buf[1024] = {};
        // 向文件流中写入
        int ret = fprintf(fptr, "row: %d", i);
        // 冲洗指定文件流
        fflush(fptr);
        // 文件指针移动到当前行开始
        fseek(fptr, -ret, SEEK_CUR); 
        // 读取该行
        fgets(buf, 1024, fptr);
        printf("%s\n", buf);
        // 文件指针换行
        fputs("\n", fptr);
        sleep(1);
    }
    fclose(fptr);
    return 0;
}
```

默认情况，流被打开时是全缓冲的，如果流引用的是终端设备，则流被打开时是行缓冲的

### 5. 关闭流

```c
#include <stdio.h>

// 在文件流关闭之前
// 1. 冲洗缓区冲中的输出数据
// 2. 丢弃缓冲区中的输入数据
// 当一个进程正常终止时
// 1. 关闭所有打开的标准 I/O 流
// 2. 还在缓冲区中的数据都会被写入到对应的文件或设备中
// 若缓冲区是标准 I/O 库分配的，则自动释放该缓冲区
int fclose(FILE *stream);
    argument:
        - stream: 待关闭的文件指针

    return:
        - 成功返回 0
        - 失败返回 EOF
```

### 6. 读写流

一旦打开流，可以在 3 中不同类型的**非格式化** I/O 中选择，对流进行读、写操作：

- 每次一个字符的 I/O
  - 每次读一个字符
  - 读取错误判断
  - 将读取字符压回流中
  - 每次写一个字符
- 每次一行的 I/O
  - 每次读一行
  - 每次写一行
- 直接 I/O（二进制 I/O、一次一个对象 I/O）
  - 二进制 I/O

格式化 I/O 由 `printf` 和 `scanf` 族函数完成

#### 6.1 读一个字符 I/O

```c
#include <stdio.h>

// 是一个函数，可以取地址，允许作为参数传递
int fgetc(FILE *stream);
    argument:
        - stream:

    return:
        - 成功返回下一个字符 unsigned char 转换为 int
          返回 int 是为 EOF 常量设计
        - 到达文件结尾或失败返回 EOF（-1）

// 可通过宏定义实现，不能作为参数传递
// 参数不应该是有副作用的表达式，因为它可能被计算多次
int getc(FILE *stream);

// 等价于 getc(stdin)
int getchar(void);
```

#### 6.2 读取错误判断

区分读写 I/O 函数是出错还是到达文件尾端，需要进行错误判断

```c
#include <stdio.h>

// 每个流在 FILE 对象中维护两个标志
// 1. 文件出错标志
// 2. 文件结束标志
// 重置这两个标志
void clearerr(FILE *stream);

//  检查文件流 stream 是否到达文件末尾
int feof(FILE *stream);
    return: 
        - 条件为真返回非 0
        - 条件为假返回 0

// 检查文件流 stream 是否发生错误
int ferror(FILE *stream);
```

#### 6.3 读取字符压回流中

```c
#include <stdio.h>

// 若压入一个序列，压入和读取是反序的，后进先出
// 不能压入 EOF
// 将字符压入缓冲区
int ungetc(int c, FILE *stream);
    argument:
        - c: 待压入字符
        - stream: 打开的文件对象指针

    return:
        - 成功返回 c
        - 失败返回 EOF
```

#### 6.4 写一个字符

```c
#include <stdio.h>

// 函数实现，可以作为参数
int fputc(int c, FILE *stream);
    argument:
        - c: 待写入字符
        - stream: 文件对象指针

    return:
        - 成功返回 c
        - 失败返回 EOF

// 可以通过宏实现，不能取地址
int putc(int c, FILE *stream);

// putc(c, stdout);
int putchar(int c);
```

#### 6.5 读一行

```c
#include <stdio.h>

// 读到换行符为止，不超过 n - 1 个字符
// s 缓冲区以 null 结尾
// 如果一行包含换行符超过 n - 1 个字节，则只返回一个不完整的行
// 下一次调用 fgets 继续读该行
char *fgets(char *s, int size, FILE *stream);
    argument:
        - s: 存放读取到的字符的缓冲区地址
        - size: 缓冲区长度
        - stream: 文件对象指针
    return:
        - 成功返回 s
        - 到达文件尾端或失败返回 NULL

// 无法指定缓冲区长度，可能造成缓冲区溢出漏洞
// 不将换行符存入缓冲区中
char *gets(char *s);
```

#### 6.6 写一行

```c
#include <stdio.h>

// 以 null 终止的字符串写到流中，null 不写出
// 不自动添加换行符
int fputs(const char *s, FILE *stream);
    argument:
        - s: 待写入字符串
        - stream: 文件对象指针

    return:
        - 成功返回非负值
        - 失败返回 EOF

// 以 null 终止的字符串写到流中，null 不写出
// 自动添加换行符，换行符也写到标准输出中 
int puts(const char *s);
```

#### 6.7 二进制 I/O

```c
#include <stdio.h>

// 只能在读取同一操作系统上的数据，跨操作系统可能异常
// 1. 同一 struct，在不同的操作系统或编译系统中，成员偏移量不同
// 2. 存储多字节的整数和浮点数的二进制格式在不同的操作系统中可能不同
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
    argument:
        - ptr: 存放二进制数据对象的缓冲区
        - size: 单个二进制数据对象的字节数
        - nmemb: 二进制数据对象的数量
        - stream: 文件对象指针

    return:
        - 读或写的对象数

size_t fwrite(const void *ptr, size_t size, size_t nmemb,
                FILE *stream);
```

### 7. 定位流

3 种定位标准 I/O 流

1. `ftell`、`fseek` 假定文件的位置可以存放在一个长整形中
2. `fteelo`、`fseeko` 使用 `off_t` 代替长整型
3. `fgetpos`、`fsetpos` 由 ISO C 引入，使用抽象数据类型 `fpos_t` 记录文件位置，这个数据类型可以根据需要定义一个足够大的数，用以记录文件位置，可以移植到非 Unix 系统

#### 7.1 ftell 与 fseek

```c
#include <stdio.h>

// 这些函数通常用于二进制文件
// 在文本文件中，可能存在换行符转换
// 字节位置可能不能准确反映字符的位置
int fseek(FILE *stream, long offset, int whence);
    argument:
        - stream: 文件流
        - offset: 偏移量
        - whence: 
            - SEEK_SET
            - SEEK_CUR
            - SEEK_END
    return:
        - 成功返回 0
        - 失败返回 -1，设置 errno

long ftell(FILE *stream);
    return:
        - 成功返回当前文件位置指示，从文件开始到当前位置的字节数
        - 失败返回 -1L，设置 errno

// 将一个流设置到文件起始位置
void rewind(FILE *stream);
```



#### 7.2 ftello 与 fseeko

```c
#include <stdio.h>

// 与 fseek 区别: offset 参数类型为 off_t
int fseeko(FILE *stream, off_t offset, int whence);
    argument:
        - stream: 文件流
        - offset: 偏移量
        - whence:
            - SEEK_CUR
            - SEEK_SET
            - SEEK_END
    return:
        - 成功返回 0
        - 失败返回 -1

// 与 ftello 区别: 函数返回值类型 off_t
off_t ftello(FILE *stream);
    return:
        - 成功返回当前文件位置
        - 失败返回 (off_t) -1
```



#### 7.3 fgetpos 与 fsetpos

```c
#include <stdio.h>

// 由 ISO C 标准引入
// 这两个函数通常处理大文件，fpos_t 类型通常能存储比 long 更大的值
// 获取当前文件指针位置
int fgetpos(FILE *stream, fpos_t *pos);
    argument:
        - stream: 文件流
        - pos: 传出参数，fpos_t 类型指针
    return:
        - 成功返回 0
        - 失败返回非 0

// 设置文件指针位置
int fsetpos(FILE *stream, const fpos_t *pos);
```



### 8. 格式化 I/O

#### 8.1 格式化输出

```c
#include <stdio.h>

// 字符串中定义的格式的输出写入到 stdout
int printf(const char *format, ...);
    return:
        - 成功返回输出到 stdout 的字符数
        - 失败返回负数

// 字符串中定义的格式的输出写入到指定的文件流 stream
int fprintf(FILE *stream, const char *format, ...);
    return:
        - 成功返回输出到文件流的字符数
        - 失败返回负数

// 字符串中定义的格式的输出写入到指定的文件描述符 fd
int dprintf(int fd, const char *format, ...);
    return:
        - 成功返回输出到文件描述符的字符数
        - 失败返回负数

// 格式化输出字符写入 str，并在数组尾端加一个 null 字节，
// 最多只会写入 size - 1 个字符
// null 不在返回值中
int sprintf(char *str, const char *format, ...);
    return:
        - 成功返回写到到字符串的字符数，不包含 null
        - 失败返回负数

// sprintf 可能造成 str 指向的缓冲区溢出
// size 指定缓冲区长度，最多只会写入 size - 1 个字符
// 超过缓冲区尾端写的所有字符会被丢弃
int snprintf(char *str, size_t size, const char *format, ...);
    return:
        - 成功返回根据格式字符串完全格式化后的字符数，不论实际上写入了多少字符
        - 失败返回负数
```

`format` 格式：`%[flags][fidwidth][precision][lenmodifier]convtype`

- 标志 flags

| 标志 | 说明                                           |
| ---- | ---------------------------------------------- |
| '    | 撇号，将整数按千位分组字符（依赖于本地化设置） |
| -    | 字段内左对齐输出                               |
| +    | 总是显示带符号转换的正负号                     |
| 空格 | 如果第一个字符不是正负号，则在前面加一个空格   |
| #    | 指定另一种转换形式，例如对于十六进制加前缀 0x  |
| 0    | 添加前导 0 进行填充                            |

- 最小字段宽度 fldwidth
  - 说明最小字段宽度
  - 转换后参数字符如果小于宽度，则多余字符位置用空格填充
  - 字段宽度是一个非负十进制数，或者是一个 `*`

- 精度 precision
  - 说明整形转换后最少输出数字位数
  - 说明浮点数转换为小数点后面的最少位数
  - 说明字符串转换后最大字节数
  - 精度是一个点 `.` 后跟着一个可选的非负十进制数或者一个 `*`

- 参数长度 lenmodifier

| 长度修饰 | 说明                                            |
| -------- | ----------------------------------------------- |
| hh       | 将相应的参数按 signed 或 unsigned char 类型输出 |
| h        | 按 signed 或 unsigned short 类型输出            |
| l        | 按 signed 或 unsigned long 或宽字符类型输出     |
| ll       | 按 signed 或 unsigned long long 类型输出        |
| j        | intmax_t 或 uintmax_t                           |
| z        | size_t                                          |
| t        | ptrdiff_t                                       |
| L        | long double                                     |

- 类型转换 convtype

| 类型转换 | 说明                                                         |
| -------- | ------------------------------------------------------------ |
| d、i     | 有符号十进制                                                 |
| o        | 无符号八进制                                                 |
| u        | 无符号十进制                                                 |
| x、X     | 无符号十六进制                                               |
| f、F     | 双精度浮点型                                                 |
| e、E     | 指数格式双精度浮点数                                         |
| g、G     | 根据转换后的值解释为 f、F、e 或 E                            |
| a、A     | 十六进制指数格式双精度浮点数                                 |
| c        | 字符（如果带长度修饰符 L，为宽字符）                         |
| s        | 字符串（如果带长度修饰符L，为宽字符）                        |
| p        | 指向 void 的指针                                             |
| n        | 到目前为止，此 printf 调用输出的字符的数量将写到指针指向的带符号整形中 |
| %        | 一个 % 字符                                                  |
| C        | 宽字符（XSI 扩展，等效于 lc）                                |
| S        | 宽字符串（XSI 扩展，等效于 ls）                              |

#### 8.2 格式化输入

```c
#include <stdio.h>

// scanf 族用于分析输入字符串，将字符串序列转换成指定类型的变量
// 除了转换说明和空白字符以外，格式字符串中的其他字符必须与输入匹配
// 如有一个字符不匹配，则停止后续处理，不再读输入的其余部分
int scanf(const char *format, ...);
    return:
        - 成功返回赋值的输入项数
        - 失败，输入错误或在任意转换前达到文件尾端，返回 EOF
int fscanf(FILE *stream, const char *format, ...);
int sscanf(const char *str, const char *format, ...);
```

`format` 格式：`%[*][fldwidth][m][lenmodifier]convtype`

- `*`：用于抑制转换，按照转换说明的其余部分对输入进行转换，但是转换结果不存放在参数中
- `fldwidth`：说明最大宽度
- `lenmodifier`：说明要转换结果赋值的参数大小
- `convtype`：类似 `printf` 族的类型转换字段，区别：输入中的带符号的数值可以赋值给无符号类型的变量
- `m`：赋值分配符，当 `%c,%s` 时，如果指定 `m`，则会自动分配内存来容纳转换的字符串。

### 9. 获取流相应的文件描述符

```c
#include <stdio.h>

// 返回与文件流 stream 关联的文件描述符
// POSIX.1 支持的扩展
int fileno(FILE *stream);
```

### 10. 创建临时文件

```c
#include <stdio.h>

// ISO C 标准 I/O 库提供了创建临时文件的函数
char *tmpnam(char *ptr);

FILE *tmpfile(void);
```



### 11. 内存流
