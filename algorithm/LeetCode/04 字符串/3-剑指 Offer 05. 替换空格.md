---
title: 剑指 Offer 05. 替换空格(简单)
date: 2023-3-21
tags:
  - 字符串
categories:
  - LeetCode必刷题
  - 字符串
abbrlink: efeda10b
---

### Describe

>  [剑指 Offer 05. 替换空格](https://leetcode.cn/problems/ti-huan-kong-ge-lcof/)
>
> 请实现一个函数，把字符串 `s` 中的每个空格替换成"%20"。 
>
> **示例 1：**
>
> ```txt
> 输入：s = "We are happy."
> 输出："We%20are%20happy."
> ```
>
> **限制：**
>
> - 0 <= s 的长度 <= 10000

### Coding

运用 C++ 的字符串重载了 + 操作符，但是需要使用额外的变量空间

```cpp
class Solution {
public:
    string replaceSpace(string s) {
        string res;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == ' ') {
                res += "%20";
            }
            else {
                res += s[i];
            }
        }
        return res;
    }
};
```

不使用额外的变量空间

![](https://s1.vika.cn/space/2023/03/21/3b71d5eb42bc433d8e15f980a6501cb4)

结束循环条件写成 `i < j` 更好（但不易理解），这个过程就是 j 在追 i 的过程，当追上了，也就说明把空格都替换完了。

```cpp
class Solution {
public:
    string replaceSpace(string s) {
        int count = 0; // 记录空格数
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == ' ') ++count;
        }
        int oldSize = s.size(); // 记录原先的字符串长度
        s.resize(s.size() + 2 * count); // 扩充字符串空间
        int newSize = s.size(); // 记录当前的字符串长度，也可以不记录，为了可读性
        for (int i = oldSize - 1, j = newSize - 1; i != j; --i, --j) {
            if (s[i] == ' ') {
                s[j] = '0';
                s[j - 1] = '2';
                s[j - 2] = '%';
                j -= 2;
            }
            else {
                s[j] = s[i];
            }
        }
        return s;
    }
};
```

