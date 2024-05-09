### Godot Document

https://docs.godotengine.org/en/stable/

### Godot Installation

https://godotengine.org/

### Godot Syntax

采用基于缩进的语法，对缩进敏感

#### Data Type

##### Dase Data Type

```gd

```



##### Array

```
# 不规定类型
var arr1:Array = [1, 2.2, "str", true]

# 规定类型
var arr2:Array[int] = [1, 2.2, false] # 1 2 0
var direction:Array[Vector2] = [Vector2(0, -1), Vector2(0, 1), 
                                Vector2(-1, 0), Vector2(1, 0)]

print(arr1.size()) # 数组长度 4
arr1.append(1) # 尾部添加元素, 1 2.2 "str" true 1
arr1.erase(true) # 从数组中移除第一个匹配的 true, 2.2 "str" true 1

# 引用变量
var tmp = arr1
tmp.clear()
print(arr1.is_empty()) # true
```

#### Funtion

```gd
# 内置虚函数
func _ready()
    pass
    
func _enter_tree()
    pass
    
func _process(delta):
    pass
    
```



#### Data Operation

```gd
var a = 1
var b = 0

print(!a, '\n',
a ^ b, '\n',
a & b, '\n',  
a | b, '\n', 
a && b, '\n',
a || b, '\n',
a and b, '\n',
a or b, '\n',
)

a += 1
# ...
```



#### Control Flow

```gd
# 控制流语句可以省略括号
# if
var a = 0
if (a > 0):
    print("positive number")
elif (a < 0):
    print("negative number")
else:
    print("the number is zero")

# for
var arr:Array[int] = [1, 2.2, false]
for ele in arr:
    print(ele)

for i in range(arr.size()):
    print(arr[i])

# while
var cnt:float = 10
while (int(cnt)):
    print(cnt)
    if (is_equal_approx(float(cnt), float(1))):
        print("over")
        break
    else:
        cnt -= float(0.1)
        continue
```



#### Input Singleton and Custom Singleton

文档中 GlobalScope 中为内置单例，独一无二的对象，不是节点，主要成员是各类 Server，可以控制图形、音效、网络、时间、电脑系统、输入等

自定义单例必须是节点类型的对象，是自定义的全局对象

#### Input Singleton

对按键进行反馈，成员 Action 手动设置

在 _process 或 _physic_process 中通过 Input 单例获取案件状况，一秒数十次检测输入情况（轮训）

`项目` - `项目设置 `- `输入映射 ` - 添加新动作

通过**控制流**可以检查结果做出相应的处理

```gd
func _process(delta):
    # "left" "right" "up" "down" 为映射动作名称
	#print(Input.get_action_strength("left")) # 按下时为真
	if Input.get_action_strength("left"):
		self.position.x -= 0.5
	if Input.get_action_strength("right"):
		self.position.x += 0.5
	if Input.get_action_strength("up"):
		self.position.y -= 0.5
	if Input.get_action_strength("down"):
		self.position.y += 0.5
```

#### Custom Singleton

`项目` - `自动加载` - 打开路径选择新建的脚本

对新建的脚本进行操作，全局可以调用

### Packaged Application

`项目` - `导出` - `添加` - `导出项目`