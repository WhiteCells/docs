### [100114. 元素和最小的山形三元组 II](https://leetcode.cn/problems/minimum-sum-of-mountain-triplets-ii/)

给你一个下标从 **0** 开始的整数数组 `nums` 。

如果下标三元组 `(i, j, k)` 满足下述全部条件，则认为它是一个 **山形三元组** ：

- `i < j < k`
- `nums[i] < nums[j]` 且 `nums[k] < nums[j]`

请你找出 `nums` 中 **元素和最小** 的山形三元组，并返回其 **元素和** 。如果不存在满足条件的三元组，返回 `-1` 。

 

**示例 1：**

```
输入：nums = [8,6,1,5,3]
输出：9
解释：三元组 (2, 3, 4) 是一个元素和等于 9 的山形三元组，因为： 
- 2 < 3 < 4
- nums[2] < nums[3] 且 nums[4] < nums[3]
这个三元组的元素和等于 nums[2] + nums[3] + nums[4] = 9 。可以证明不存在元素和小于 9 的山形三元组。
```

**示例 2：**

```
输入：nums = [5,4,8,7,10,2]
输出：13
解释：三元组 (1, 3, 5) 是一个元素和等于 13 的山形三元组，因为： 
- 1 < 3 < 5 
- nums[1] < nums[3] 且 nums[5] < nums[3]
这个三元组的元素和等于 nums[1] + nums[3] + nums[5] = 13 。可以证明不存在元素和小于 13 的山形三元组。
```

**示例 3：**

```
输入：nums = [6,5,4,3,4,5]
输出：-1
解释：可以证明 nums 中不存在山形三元组。
```

 

**提示：**

-  $3 <= nums.length <= 10^5$
-  $1 <= nums[i] <= 10^8$

### 方法1：前后缀分解 + 枚举

维护两个最小值数组，$pre[i]$ 维护从左向右 $0$ 到 $i$ （包括 $i$ ）的最小值， $suf[i]$ 维护从右向左 $n-2$ 到 $0$ 的最小值，枚举 $j$ ，$j$ 下标左侧的最小值为 $pre[j-1]$ ，$j$ 下标右侧的最小值为 $suf[j + 1]$ 

```cpp
class Solution {
public:
    int minimumSum(vector<int>& nums) {
        int n = nums.size();
        int pre[n]; // 前缀
        pre[0] = nums[0];
        for (int i = 1; i < n; ++i) { // 1 -> (n - 1)
            pre[i] = min(pre[i - 1], nums[i]);
        }
        int suf[n]; // 后缀
        suf[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; --i) { // 0 <- (n - 2)
            suf[i] = min(suf[i + 1], nums[i]);
        }
        int res = INT_MAX;
        // 枚举 j
        for (int j = 1; j < n - 1; ++j) { // 1 -> n - 2
            if (nums[j] > pre[j - 1] && nums[j] > suf[j + 1]) {
                res = min(res, nums[j] + pre[j - 1] + suf[j + 1]);
            }
        }
        return INT_MAX == res ? -1 : res;
    }
};
```

- 时间复杂度： $O(n)$
- 空间复杂度： $O(n)$

优化 $pre[i]$ 数组，在从左到右枚举 $j$ 时，左侧最小值可以使用一个数来维护

```cpp
class Solution {
public:
    int minimumSum(vector<int>& nums) {
        int n = nums.size();
        int pre = nums[0];
        int suf[n];
        suf[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; --i) { // 0 <- (n - 2)
            suf[i] = min(suf[i + 1], nums[i]);
        }
        int res = INT_MAX;
        // 枚举 j
        for (int j = 1; j < n - 1; ++j) { // 1 -> (n - 2)
            if (nums[j] > pre && nums[j] > suf[j + 1]) {
                res = min(res, nums[j] + pre + suf[j + 1]);
            }
            pre = min(pre, nums[j]);
        }
        return INT_MAX == res ? -1 : res;
    }
};
```

- 时间复杂度： $O(n)$
- 空间复杂度： $O(n)$

> 对于此类问题，当数较多时，采用枚举中间的数
