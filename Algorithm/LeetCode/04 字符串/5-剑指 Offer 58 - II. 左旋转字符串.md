---
title: 剑指 Offer 58 - II. 左旋转字符串(简单)
date: 2023-3-23
tags:
  - 字符串
categories:
  - LeetCode必刷题
  - 字符串
abbrlink: b7304e66
---

### Describe

> [剑指 Offer 58 - II. 左旋转字符串](https://leetcode.cn/problems/zuo-xuan-zhuan-zi-fu-chuan-lcof/)
>
> 字符串的左旋转操作是把字符串前面的若干个字符转移到字符串的尾部。请定义一个函数实现字符串左旋转操作的功能。比如，输入字符串"abcdefg"和数字2，该函数将返回左旋转两位得到的结果"cdefgab"。
>
> **示例 1：**
>
> ```txt
> 输入: s = "abcdefg", k = 2
> 输出: "cdefgab"
> ```
>
> **示例 2：**
>
> ```txt
> 输入: s = "lrloseumgh", k = 6
> 输出: "umghlrlose"
> ```
>
> **限制：**
>
> - `1 <= k < s.length <= 10000`

### Coding

第一次的思路

字符串为 `abcdefg` k = `2`

1. 重新给字符串分配大小，原来大小上加 n 的长度。`abcdefg__`
2. 将字符串前 n 个字符放到新字符串末尾。`abcdefgab`
3. 将新字符串整体向前移动 n 次。`cdefgabab`
4. 缩小新字符串大小为旧字符串的大小。`cdefgab`

```cpp
class Solution {
public:
    string reverseLeftWords(string s, int n) {
        int slow = 0, fast = s.size();
        int len = s.size(); // 记录旧字符串的长度
        // 1、重新给字符串分配大小，原来大小上加 n 的长度
        s.resize(len + n);
        int tmp = n;
        // 2、将字符串前 n 个字符放到新字符串末尾
        while (tmp--) {
            s[fast++] = s[slow++];
        }
        slow = 0;
        fast = n;
        // 3、将新字符串整体向前移动 n 次（fast 结束条件 < 新字符串的长度）
        for (; fast < s.size(); ++fast) {
            s[slow++] = s[fast];
        }
        // 4、缩小新字符串大小为旧字符串的大小
        s.resize(len);

        return s;
    }
};
```

第二次思路

字符串为 `abcdefg` k = `2`

1. 反转 n 前面的字符串（注意 n 为逻辑下标）。`bacdefg`
2. 反转 n 后面的字符串（包括 n）。`bagfed`
3. 反转整个字符串。 `defgab`

```cpp
class Solution {
public:
    // 反转字符串，start、end 为物理下标
    void reverseStr(string& s, int start, int end) {
        for (int i = start, j = end; i < j; ++i, --j) {
            s[i] ^= s[j];
            s[j] ^= s[i];
            s[i] ^= s[j];
        }
    }
    string reverseLeftWords2(string s, int n) {
        // 1、反转 n 前面的字符串，n 为逻辑下标
        reverseStr(s, 0, n - 1);
        // 2、反转 n 后面的字符串
        reverseStr(s, n, s.size() - 1);
        // 3、反转 s 整个字符串
        reverseStr(s, 0, s.size() - 1);

        return s;
    }
};
```

这道题如果使用额外空间还是很简便

1. 新建一个 string
2. 第一个 for 遍历 n 到 字符串长度 - 1
3. 第二个 for 遍历 0 到 n - 1

```cpp
class Solution {
public:
    string reverseLeftWords(string s, int n) {
        string ans;
        for(int i = n; i < s.size(); i++) ans += s[i];
        for(int i = 0; i < n; i++) ans += s[i];
        return ans;
    }
};
```

字符串库版本（仅供“娱乐”）

```cpp
class Solution {
public:
	string reverseLeftWords(string s, int n) {
		return s.substr(n) + s.substr(0, n);
    }
}
```

