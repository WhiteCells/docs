### LaTex Math Symbols

[Latex Documents](https://kapeli.com/cheat_sheets/LaTeX_Math_Symbols.docset/Contents/Resources/Documents/index)

`$x_{2}$` 下标 $x_{2}$

`$x^{2}$` 上标 $x^{2}$

`$\times$` 乘 $\times$

`$\div$` 除 $\div$

`$\leqslant$` 小于等于 $\leqslant$

`$\leq$` or `$\le$` 小于等于 $\le$

`$\lt$` or `$<$` 小于 $<$

`$\geqslant$` 大于等于 $\geqslant$

`$\geq$` or `$\ge$` 大于等于  $\ge$

`$\gt$` or `$>$` 大于 $>$

`$\neq$` or `$\ne$` 不等于 $\ne$

`$\approx$` 约等于 $\approx$

`$\sin$` 正弦函数 $\sin$

`$\cos$` 余弦函数 $\cos$

`$\tan$` 正切函数 $\tan$

`$\frac{a}{b}$` 分数 $\frac{a}{b}$

`$\dfrac{a}{b}$` 分数 $\dfrac{a}{b}$

`${a\over b}$` 分数 ${a\over b}$

`$\sqrt[3]{5}$` 开方 $\sqrt[3]{5}$

`$\sim$` $\sim$

`$\lceil x \rceil$` 向上取整 $\lceil x \rceil$

`$\lfloor x \rfloor$` 向下取整 $\lfloor x\rfloor$

`$\lvert x \rvert$` or `$|x|$` 绝对值 $|x|$ 

`$C_n^m$ ` 组合 $C_n^m$

多行公式

```
$$
\left\{
\begin{array}{l}
a_1x+b_1y+c_1z=d_1\\
a_2x+b_2y+c_2z=d_2\\
a_3x+b_3y+c_1z=d_3
\end{array}
\right.
$$

```

$$
\left\{
\begin{array}{l}
a_1x+b_1y+c_1z=d_1\\
a_2x+b_2y+c_2z=d_2\\
a_3x+b_3y+c_1z=d_3
\end{array}
\right.
$$

$$
\begin{equation}
\dot{{x}}=f({x})
=\left\{
	\begin{array}{ll}
		f_{1}({x}) & \boldsymbol{x} \in S_{1} \\
		f_{2}({x}) & \boldsymbol{x} \in S_{2}
	\end{array}\right.
\end{equation}
$$



#### 积分

```
$\iint\limits_D\left(\dfrac{\partial Q}{\partial x}-\dfrac{\partial P}{\partial y}\right){\rm d}x{\rm d}y=\oint\limits_LP{\rm d}x+Q{\rm d}y$
```

$\iint\limits_D\left(\dfrac{\partial Q}{\partial x}-\dfrac{\partial P}{\partial y}\right){\rm d}x{\rm d}y=\oint\limits_LP{\rm d}x+Q{\rm d}y$

#### 极限

```
$\lim\limits_{n\to\infin}(1+\dfrac{1}{n})^n=e$
```

$\lim\limits_{n\to\infin}(1+\dfrac{1}{n})^n=e$

#### 累加

```
$\sum\limits_{i=1}^n\dfrac{1}{n^2}$
```

$\sum\limits_{i=1}^n\dfrac{1}{n^2}$

#### 累乘

```
$\prod\limits_{i=1}^n\dfrac{1}{n^2}$
```

$\prod\limits_{i=1}^n\dfrac{1}{n^2}$

#### 交集

```
$\bigcup\limits_{i=1}^n\dfrac{1}{n^2}$
```

$\bigcup\limits_{i=1}^n\dfrac{1}{n^2}$

#### 并集

```
$\bigcap\limits_{i=1}^n\dfrac{1}{n^2}$
```

$\bigcap\limits_{i=1}^n\dfrac{1}{n^2}$

### Markdown 

#### 任务列表

```
- [ ]
```

快捷键 ctrl + shift + x

#### 引用

```
> 
```

快捷键 ctrl + shift + q 

#### 链接

```
[显示内容](网址)
```

快捷键 ctrl + k

#### 脚注

```
[^文本]

[^文本]:解释说明
```



#### 图片

```
![显示的文字](图片路径)
```

快捷键 ctrl + shift + i

#### 表格

```
| | |回车
```

快捷键 ctrl + t

#### 公式

行中公式

```
$$
```

独立公式 快捷键 ctrl + shift + m

```
$$
$$
```

#### 代码块

当行代码

快捷键：ctrl + shift + ~

```
`code`
```

代码块

```
~~~
~~~
```

快捷键 ctrl + shift + k

#### 文本操作

**加粗** ctrl + b

*倾斜* ctrl + i

<u>下划线</u> ctrl + u

~~删除线~~ alt + shift + 5

#### Typora 操作

偏好：ctrl + , 

关闭：ctrl + w

快速打开：ctrl + p

打开：ctrl + o

新建窗口：ctrl + shift + n

新建：ctrl + n

大纲：ctrl + shift + 1

文档列表：ctrl + shift + 2

文件树：ctrl + shift + 3

实际大小：ctrl + shift + 9

显示/隐藏侧边栏：ctrl + shift + l

减少缩进：ctrl + [ 

增加缩进： Ctrl + ] 

提升标题等级：Ctrl + =

降低标题等级：Ctrl + -

选取一整行：ctrl + l

开发者工具：shift + F12

查找：F3、ctrl + f

专注模式：F8

打字机模式：F9

全屏：F11

### UML

[UML mermaid](https://mermaid.js.org/intro/)

代码块中增加 `mermaid` 标识

| 关系  | 含义 |
| ----- | ---- |
| --\|> | 继承 |
| ..\|> | 实现 |
| --o   | 聚合 |
| --*   | 组合 |
| ..>   | 依赖 |
| -->   | 关联 |

实现

```mermaid
classDiagram
class A{
    
}

class B {
    
}

B..|>A
```
