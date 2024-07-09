### 注释

- 不明所以的注释不会要写。日后再看只会徒增麻烦

### BUG

1. 出乎意料的结果
   1. 检查索引是否越界
   2. 检查循环体的条件
   3. 检查数据是否初始化
   4. 检查数据是否溢出



等号判断将 常量 放在 `==` 左边，避免写成 `=` 的情况

```cpp
if(0 == val){
    ;
}
```





两个分支中有一个分支有结束条件则这个分支可以简化成单分支，优先判断有结束条件的情况。

```cpp
if(0 == val){
    ++val;
} else {
    return;
}

// 简化
if(0 != val){
    return;
}
++val;
```



将一个只有 0 和 1 的数组全部取反

```cpp
vector<int> nums{ 1, 0, 1, 0 };

for(auto& num : nums){
    num = 1 - num;
}

// or
for(auto& num : nums){
    num = num == 1 ? 0 : 1;
}

// or
for(auto& num : nums){
    num != num;
}
```



容器长度的数据类型是 `size_t`，就是无符号类型，在遍历到倒数第一个是需要注意数据溢出问题

```cpp
vector<int> nums{ 1, 0, 1, 0 };

// for (int i = 0; i < nums.size() - 1; ++i) { // bad
for(int i = 0; i + 1 < nums.size(); ++i) {
	;
}

// or
const size_t len = nums.size();
for(int i = 0; i < len - 1; ++i){
    ;
}
```
