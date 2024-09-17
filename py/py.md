```python
"""
comment
"""

i1 = 1                 # 整数
i2 = 1.1               # 浮点数
i3 = 1 + 4j            # 复数
i4 = True              # 布尔
i5 = "test"            # 字符串
i6 = 'test'            # 字符串
i7 = """testtest"""    # 字符串
i8 = [1, 2]            # 列表
i9 = {1, 2}            # 集合
i10 = {1 : "", 2 : ""} # 字典

print(i7)
print(type(1))                # int
print(type(1.1))              # float
print(type(""))               # str
print(type([1, 2]))           # list
print(type({1, 2}))           # set
print(type({1 : "", 2 : ""})) # dict

j1 = int(1.1)
j2 = float(1.1)
j3 = bool(0)
j4 = str(1.2)
j5 = int("1")
j6 = float("1.1")
print(j4)
print(j5)
print(j6)

print(1 / 1)         # 1.0
print(type(1 / 1))   # float
print(type(1 / 1.0)) # float

# %
print(3 // 2)
print(3 // 2.0) # 1.0

# pow
print(2 ** 3.1)

x = 1
x -= 1
# x-- error
# --x error
print(x)

print("str1" "str2")
# + 只能拼接字符串
print("str1" + "str2")
tmp = 1
# print("tmp: " + tmp)
print("tmp:", tmp)

print(len("str1"))

# format
print("%s" %tmp) 
print("%d" %tmp)
print("%s %s" %(tmp, tmp))

tmp2 = 110.011
print("%f" %tmp2)
print("%.0f" %tmp2)
print("%.1f" %tmp2)
print("%.2f" %tmp2)
print("%2.0f" %tmp2)
print("%4.0f" %tmp2)

print(f"{tmp}" " - " f"{tmp2}")

k1, k2, k3 = 1, 2.2, True
print(k1, k2, k3)

# input -> str -> type()
# l = input("input: ")
# print("l: ", int(l))

if True:
    print("")
elif True:
    print("")
else:
    print("")

x = 1
while x:
    print("x")
    x -= 1

for c in "string":
    print(c)
    break

# [)
for i in range(1, 10):
    print(i)
    break

for i in range(1, 10, 3):
    print(i)
    continue
    print(0)

# function
def f(
    x: int, 
    y: int
) -> int:
    """
    :param x: b
    :param y: a
    :return: a + b
    """
    print(x, y)
    return x + y

print(f) # f ptr
print(type(f)) # function
print(f(1, 2))
print(f(1.1, 2.2))
print(f(1.1, 2.2))
print(f(1.1, 2.2))

def f2() -> None:
    return 1

print(f2())

if None: # False
    print()
else:
    print()

##################################################
### list

list = []

list.append(1)
list.append(1.1)
list.append("str")

for ele in list:
    print(type(ele))
    print(ele)

for i in range(0, len(list)):
    print(list[i])
    
for i in range(1, len(list) + 1):
    print(list[-i])
    
print(list.index("str"))

list.insert(0, [1.1, "str1"])

print(list[0][1])

# 用于将一个可迭代对象（如列表、元组、集合等）的所有元素添加到列表的末尾。
list.extend([1, 2, 3])

list.append([3, 4, 5])

print(list[len(list) - 1]) # [3, 4, 5]
print(list[len(list) - 2]) # 3

pop_ele = list.pop(0)
print(pop_ele) # [1.1, "str1"]
print(list[0]) # 1

del list[0]
print(list[0])

del list[0]
print(list[0])

list = [0, 1, 1, 2]

print(list.count(1)) # 2

list.remove(1)
print(list) # [0, 1, 2]

list.clear()
print(list) # []

##################################################
### tuple

tuple1 = (1, 2.2, "str")
# tuple() 构造函数创建元组，你需要传递一个可迭代对象
tuple2 = tuple([1, 2, "str"])
# tuple2 = tuple(1, 2.2, "str")

print(len(tuple1))

print(tuple1.index(1))

print(tuple1.count(1))

for ele in tuple1:
    print(ele)

for ele in tuple2:
    print(ele)

t = (1)
print(type(t)) # <class 'int'>

t2 = (1, )
print(type(t2)) # <class 'tuple'>

##################################################
### str

string1 = "string"
print(string1[1])
print(string1.index('r'))
print(string1.index("tr"))
print(string1.count('s'))
print(string1.find('t'))
print(string1.islower())

string2 = "this  is test"
word_list = string2.split(' ') # ['this', '', 'is', 'test']
print(word_list)

string3 = "  this "
print(string3.strip()) # this

string4 = "is this si"
print(string4.strip("is")) #  this

##################################################
# (序列)切片，得到一个新序列
list3 = [1, 2, 3, 4, 5, 6]

# [)
new_list = list3[1:2]
print(new_list) # [2]

new_list = list3[1:5:2]
print(new_list) # [2, 4]

new_list = list3[5:1:-1]
print(new_list) # [6, 5, 4, 3]

##################################################
### set
set1 = {1, 2.2, 2.2, "str"}
print(set1) # {1, 2.2, 'str'}
for ele in set1:
    print(ele)
set1.remove(2.2)
set1.pop()
set1.add(True)
print(set1)

set1.clear()
```

