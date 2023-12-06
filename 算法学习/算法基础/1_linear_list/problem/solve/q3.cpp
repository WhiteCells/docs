#include <iostream>
#include <string.h>

using namespace std;

int l[100001];
int r[100001];
bool flag;

void Init(int n) {
    // 带头节点
    for (int i = 1; i <= n; ++i) {
        l[i] = i - 1;
        r[i - 1] = i;
        // r[i - 1] = i % (n + 1);
    } // 链表中值都不相同，所以用 l[i] 表示 i 的下一个值，r[i] 表示 i 的上一个值 
    l[0] = n;
}

// 连接 x y，同时可用来跳过 x、y 之间的节点
void Link(int x, int y) {
    r[x] = y;
    l[y] = x;
}

int main() {
    int n, m, a, x, y, k = 0;
    while (cin >> n >> m) {
        Init(n);
        flag = false;
        for (int i = 0; i < m; ++i) {
            cin >> a;
            // 翻转链表
            if (4 == a) {
                flag = !flag; // 更改 1 和 2 的操作
            }
            else {
                cin >> x >> y;
                // 交换 x y，且 x y 相邻
                if (3 == a && r[y] == x) {
                    swap(x, y);
                }
                // 翻转过，则 a == 1 和 a == 2 换操作
                if (3 != a && flag) {
                    a = 3 - a;
                }
                // 将 x 放在 y 左边，实际 x 在 y 的左边
                if (1 == a && l[y] == x) {
                    continue;
                }
                // 将 x 放在 y 右边，实际 x 在 y 的右边
                if (2 == a && r[y] == x) {
                    continue;
                }
                int xl = l[x], xr = r[x], yl = l[y], yr = r[y];
                // x 放到 y 的左边
                if (1 == a) {
                    // 删除 x
                    Link(xl, xr);
                    // x 插入 y 的左边
                    Link(yl, x);
                    Link(x, y);
                }
                // x 放到 y 的右边
                else if (2 == a) {
                    // 删除 x
                    Link(xl, xr);
                    // x 插入 y 的右边
                    Link(x, yr);
                    Link(y, x);
                }
                // x y 交换位置
                else if (3 == a) {
                    // x y 相邻
                    if (r[x] == y) {
                        Link(xl, y);
                        Link(y, x);
                        Link(x, yr);
                    }
                    else {
                        Link(xl, y);
                        Link(y, xr);
                        Link(yl, x);
                        Link(x, yr);
                    }
                }
            }
        }
        long long sum = 0;
        
        int t = 0;
        for (int i = 1; i <= n; ++i) {
            t = r[t]; // 按连接顺序从头第一个（不包含头节点）开始取出链表的值
            if (i % 2) {
                sum += t;
            }
        }
        // 如果链表反转过，修改 sum
        if (flag && n % 2 == 0) {
            sum = (long long)n * (n + 1) / 2 - sum; // 等差公式
        }
        cout << "Case " << k + 1 << ": " << sum << '\n';
    }
    return 0;
}