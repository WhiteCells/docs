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

```markdown
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

```latex
$\iint\limits_{D} \left(\dfrac{\partial Q}{\partial x}-\dfrac{\partial P}{\partial y}\right){\rm d}x{\rm d}y=\oint\limits_LP{\rm d}x+Q{\rm d}y$
```

$\iint\limits_D\left(\dfrac{\partial Q}{\partial x}-\dfrac{\partial P}{\partial y}\right){\rm d}x{\rm d}y=\oint\limits_LP{\rm d}x+Q{\rm d}y$

#### 极限

```latex
$\lim\limits_{n\to\infin}(1+\dfrac{1}{n})^n=e$
```

$\lim\limits_{n\to\infin}(1+\dfrac{1}{n})^n=e$

#### 累加

```latex
$\sum\limits_{i=1}^{n} \dfrac{1}{n^2}$
```

$\sum\limits_{i=1}^n\dfrac{1}{n^2}$

#### 累乘

```latex
$\prod\limits_{i=1}^{n} \dfrac{1}{n^2}$
```

$\prod\limits_{i=1}^n\dfrac{1}{n^2}$

#### 交集

```latex
$\bigcup\limits_{i=1}^{n} \dfrac{1}{n^2}$
```

$\bigcup\limits_{i=1}^n\dfrac{1}{n^2}$

#### 并集

```latex
$\bigcap\limits_{i=1}^{n} \dfrac{1}{n^2}$
```

$\bigcap\limits_{i=1}^n\dfrac{1}{n^2}$

### Markdown 

#### 任务列表

```markdown
- [ ]
```

快捷键：<kbd>ctrl</kbd> <kbd>shift</kbd> <kbd>x</kbd>

#### 引用

```markdown
> 
```

快捷键：<kbd>ctrl</kbd> <kbd>shift</kbd> <kbd>q</kbd> 

#### 链接

```markdown
[显示内容](网址)
```

快捷键：<kbd>ctrl</kbd> <kbd>k</kbd>

#### 脚注

```markdown
[^文本]

[^文本]:解释说明
```

#### 图片

```markdown
![显示的文字](图片路径)
```

快捷键：<kbd>ctrl</kbd> <kbd>shift</kbd> <kbd>i</kbd>

#### 表格

```markdown
| | |回车
```

快捷键：<kbd>ctrl</kbd> <kbd>t</kbd>

#### 公式

行内公式

```latex
$x_1$
$$x_1$$
```

多行公式

```latex
$$
$$
```

#### 代码块

单行代码

快捷键：<kbd>ctrl</kbd> <kbd>shift</kbd> <kbd>~</kbd>

```
`code`
```

代码块

```
~~~
~~~
```

快捷键 <kbd>ctrl</kbd> <kbd>shift</kbd> <kbd>k</kbd>

#### 文本操作

**加粗** <kbd>ctrl</kbd> <kbd>b</kbd>

*倾斜* <kbd>ctrl</kbd> <kbd>i</kbd>

<u>下划线</u> <kbd>ctrl</kbd> <kbd>u</kbd>

~~删除线~~ <kbd>alt</kbd> <kbd>shift</kbd> <kbd>5</kbd>

==高亮==

### UML

[UML mermaid](https://mermaid.js.org/intro/)

#### classDiagram

代码块中增加 **classDiagram** 标识

| 关系  | 含义 |
| ----- | ---- |
| --\|> | 继承 |
| ..\|> | 实现 |
| --o   | 聚合 |
| --*   | 组合 |
| ..>   | 依赖 |
| -->   | 关联 |

##### 继承

~~~markdown
```mermaid
classDiagram
class A
class B
B --|> A
```
~~~

```mermaid
classDiagram
class A
class B
B --|> A
```

##### 实现

~~~markdown
```mermaid
classDiagram
class A
class B
B..|>A
```
~~~

```mermaid
classDiagram
class A
class B
B..|>A
```

##### 聚合

~~~markdown
```mermaid
classDiagram
class A
class B
A --o B
```
~~~

```mermaid
classDiagram
class A
class B
A --o B
```

##### 组合

~~~markdown
```mermaid
classDiagram
class A
class B
A --* B
```
~~~

```mermaid
classDiagram
class A
class B
A --* B
```

##### 依赖

~~~markdown
```mermaid
classDiagram
class A
class B
A ..> B
```
~~~

```mermaid
classDiagram
class A
class B
A ..> B
```

##### 关联

~~~markdown
```mermaid
classDiagram
class A
class B
A --> B
```
~~~

```mermaid
classDiagram
class A
class B
A --> B
```
