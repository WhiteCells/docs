### [122. 买卖股票的最佳时机 II](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/)

给你一个整数数组 `prices` ，其中 `prices[i]` 表示某支股票第 `i` 天的价格。

在每一天，你可以决定是否购买和/或出售股票。你在任何时候 **最多** 只能持有 **一股** 股票。你也可以先购买，然后在 **同一天** 出售。

返回 *你能获得的 **最大** 利润* 。



**示例 1：**

```
输入：prices = [7,1,5,3,6,4]
输出：7
解释：在第 2 天（股票价格 = 1）的时候买入，在第 3 天（股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5 - 1 = 4 。
随后，在第 4 天（股票价格 = 3）的时候买入，在第 5 天（股票价格 = 6）的时候卖出, 这笔交易所能获得利润 = 6 - 3 = 3 。
总利润为 4 + 3 = 7 。
```

**示例 2：**

```
输入：prices = [1,2,3,4,5]
输出：4
解释：在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5 - 1 = 4 。
总利润为 4 。
```

**示例 3：**

```
输入：prices = [7,6,4,3,1]
输出：0
解释：在这种情况下, 交易无法获得正利润，所以不参与交易可以获得最大利润，最大利润为 0 。
```



**提示：**

- `1 <= prices.length <= 3 * 10^4`
- `0 <= prices[i] <= 10^4`

#### 递归

定义 $dfs(i,0)$ 表示到第 $i$ 天结束时，未持有股票的最大利润

定义 $dfs(i,1)$ 表示到第 $i$ 天结束时，持有股票的最大利润

由于第 $i-1$ 天的结束就是第 $i$ 天的开始

$dfs(i-1,·)$ 表示到第 $i$ 天开始的最大利润

$dfs(i,0)=max(dfs(i-1,0),dfs(i-1,1)+prices[i])$

$dfs(i,1)=max(dfs(i-1,1),dfs(i-1,0)-prices[i])$

**递归边界:**

$dfs(-1,0)=0$ , 第 0 天开始未持有股票，利润 0

$dfs(-1,1)=-\infty$ , 第 0 天开始不可能持有股票 

**递归入口:**

$max(dfs(n-1, 0),dfs(n-1,1))$ 

想要利润最大，那么最后一天一定不能再持有股票

$max(dfs(n-1, 0),dfs(n-1,1))=dfs(n-1,0)$ 

```cpp
class Solution {
public:
    int maxProfit(vector<int> &prices) {
        int n = prices.size();
        vector<vector<int>> menm(n, vector<int>(2, -1));
        function<int(int, bool)> dfs = [&](int i, bool hold)->int {
            if (i < 0) {
                return hold ? INT_MIN : 0;
            }
            if (-1 != menm[i][hold]) { // 当以 i 和 hold 为参数递归计算的值存在时，则直接跳出当前递归
                return menm[i][hold];
            }
            if (hold) {
                return menm[i][true] = max(dfs(i - 1, true), dfs(i - 1, false) - prices[i]);
            }
            return menm[i][false] = max(dfs(i - 1, false), dfs(i - 1, true) + prices[i]);
        };
        return dfs(n - 1, false); // return max(dfs(n - 1, false), dfs(n - 1, true)); 最后一天一定不能持有股票
    }
};
```

#### 动态规划

$dp[0][0]=0$

$dp[0][1]=-\infty$

$dp[i][0]=max(dp[i-1][0],dp[i-1][1]-prices[i])$

$dp[i][1]=max(dp[i-1][1],dp[i-1][0]+prices[i])$

考虑到 $i-1$ 可能会越界:

$dp[i+1][0]=max(dp[i][0],dp[i][1]+prices[i])$

$dp[i+1][1]=max(dp[i][1],dp[i][0]-prices[i])$

结果为:

$dp[n][0]$

```cpp
class Solution {
public:
    int maxProfit(vector<int> &prices) {
        int n = prices.size();
        vector<vector<int>> dp(n + 1, vector<int>(2, 0));
        dp[0][1] = INT_MIN;
        for (int i = 0; i < n; ++i) {
            dp[i + 1][0] = max(dp[i][0], dp[i][1] + prices[i]);
            dp[i + 1][1] = max(dp[i][1], dp[i][0] - prices[i]);
        }
        return dp[n][0];
    }
};
```

$dp[i+1]$ 只使用到 $dp[i]$ ，故可滚动数组进行空间优化

```cpp
class Solution {
public:
    int maxProfit(vector<int> &prices) {
        int n = prices.size(), dp0 = 0, dp1 = INT_MIN;
        for (int i = 0; i < n; ++i) {
            dp0 = max(dp0, dp1 + prices[i]);
            dp1 = max(dp1, dp0 - prices[i]);
        }
        return dp0;
    }
};
```



### [309. 买卖股票的最佳时机含冷冻期](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-with-cooldown/)

给定一个整数数组`prices`，其中第 `prices[i]` 表示第 `i` 天的股票价格 。

设计一个算法计算出最大利润。在满足以下约束条件下，你可以尽可能地完成更多的交易（多次买卖一支股票）:

- 卖出股票后，你无法在第二天买入股票 (即冷冻期为 1 天)。

**注意：**你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。



**示例 1:**

```
输入: prices = [1,2,3,0,2]
输出: 3 
解释: 对应的交易状态为: [买入, 卖出, 冷冻期, 买入, 卖出]
```

**示例 2:**

```
输入: prices = [1]
输出: 0
```



**提示：**

- `1 <= prices.length <= 5000`
- `0 <= prices[i] <= 1000`

#### 递归

当前属于持有股票状态，从之前的未持有股票到持有股票有一个冷冻期，所以最少是在当前的前两天购买股票:

$dfs(i,1)=max(dfs(i-1,1),dfs(i-2,0)-prices[i])$

当前属于未持有股票状态，从持有股票状态到未持有股票状态没有冷冻期:

$dfs(i,0)=max(dfs(i-1,0),dfs(i-1,1)+prices[i])$

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> menm(n, vector<int>(2, -1));
        function<int(int, bool)> dfs = [&](int i, bool hold)->int {
            if (i < 0) {
                return hold ? INT_MIN : 0;
            }
            if (-1 != menm[i][hold]) {
                return menm[i][hold];
            }
            if (hold) {
                return menm[i][true] = max(dfs(i - 1, true), dfs(i - 2, false) - prices[i]);
            }
            return menm[i][false] = max(dfs(i - 1, false), dfs(i - 1, true) + prices[i]);
        };
        return dfs(n - 1, 0);
    }
};
```

#### 动态规划

$dp[0][0]=0$

$dp[0][1]=-\infty$

$dp[i][0]=max(dp[i-1][0], dp[i-1][1]+prices[i])$

$dp[i][1]=max(dp[i-1][1],dp[i-2][0]-prices[i])$

考虑到 $i-2$ 可能越界:

$dp[1][0]=0$

$dp[1][1]=-\infty$

$dp[i+2][0]=max(dp[i+1][0], dp[i+1][1]+prices[i])$

$dp[i+2][1]=max(dp[i+1][1],dp[i][0]-prices[i])$

```cpp
class Solution {
public:
    int maxProfit(vector<int> &prices) {
        int n = prices.size();
        vector<vector<int>> dp(n + 2, vector<int>(2, 0));
        dp[1][1] = INT_MIN; // 注意初始化 dp[1][1]
        for (int i = 0; i < n; ++i) {
            dp[i + 2][0] = max(dp[i + 1][0], dp[i + 1][1] + prices[i]);
            dp[i + 2][1] = max(dp[i + 1][1], dp[i][0] - prices[i]);
        }
        return dp[n + 1][0];
    }
};
```



### [188. 买卖股票的最佳时机 IV](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-iv/)

给你一个整数数组 `prices` 和一个整数 `k` ，其中 `prices[i]` 是某支给定的股票在第 `i` 天的价格。

设计一个算法来计算你所能获取的最大利润。你最多可以完成 `k` 笔交易。也就是说，你最多可以买 `k` 次，卖 `k` 次。

**注意：**你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。



**示例 1：**

```
输入：k = 2, prices = [2,4,1]
输出：2
解释：在第 1 天 (股票价格 = 2) 的时候买入，在第 2 天 (股票价格 = 4) 的时候卖出，这笔交易所能获得利润 = 4-2 = 2 。
```

**示例 2：**

```
输入：k = 2, prices = [3,2,6,5,0,3]
输出：7
解释：在第 2 天 (股票价格 = 2) 的时候买入，在第 3 天 (股票价格 = 6) 的时候卖出, 这笔交易所能获得利润 = 6-2 = 4 。
  随后，在第 5 天 (股票价格 = 0) 的时候买入，在第 6 天 (股票价格 = 3) 的时候卖出, 这笔交易所能获得利润 = 3-0 = 3 。
```



**提示：**

- `1 <= k <= 100`
- `1 <= prices.length <= 1000`
- `0 <= prices[i] <= 1000`

#### 递归

定义 $dfs(i,j,0)$ 表示第 $i$ 天结束时完成至多 $j$ 次交易，未持有股票的最大利润。

定义 $dfs(i,j,1)$ 表示第 $i$ 天结束时完成至多 $j$ 次交易，持有股票的最大利润。

每卖出一次算一次交易

$dfs(i,j,0)=max(dfs(i-1,j,0),dfs(i-1,j,1)+prices[i])$

$dfs(i,j,1)=max(dfs(i-1,j,1),dfs(i-1,j-1,0)-prices[i])$

```CPP

```

