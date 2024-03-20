#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

// time  O(n^2)
// space O(n)
void Solve1() {
    int T = 0;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m; // n 个任务，m 下标需要用时
        int q[2 * n];
        int front = 0, rear = 0, ans = 0;
        for (int i = 0; i < n; ++i) {
            cin >> q[i];
            ++rear;
        }
        while (1) {
            // 标记队头最大
            bool flag = true;
            for (int i = front + 1; i < rear; ++i) {
                if (q[i] > q[front]) {
                    flag = false;
                    break;
                }
            }
            // 队头最大
            if (flag) {
                ++ans;
                if (front == m) {
                    break;
                }
                else {
                    ++front;
                }
            }
            // 队头非最大
            else {
                if (front == m) {
                    m = rear; // 更新目标位置
                }
                // 队头放到队尾，同时更新队头、队尾
                q[rear++] = q[front++];
            }
        }
        cout << ans << '\n';
    }
}

void Solve2() {
    int T = 0;
    cin >> T;
    while (T--) {
        queue<int> q; // 存放下标
        vector<int> a, b; // a 存放优先级，b 存放降序的优先级
        int n = 0, m = 0;
        cin >> n >> m;
        for (int i = 0; i < n; ++i) {
            int priority = 0;
            cin >> priority;
            a.push_back(priority);
            b.push_back(priority);
            q.push(i);
        }
        sort(b.begin(), b.end(), greater<int>()); // 优先级降序
        int b_index = 0, res = 0;
        while (!q.empty()) {
            int max_priority = b[b_index]; // 取大优先级
            int leader_index = q.front(); // 队头下标
            // 队头优先级 < 最大优先级
            if (a[leader_index] < max_priority) {
                q.pop();
                q.push(leader_index);
            }
            // 队头优先级 >= 最大优先级
            else {
                if (leader_index == m) {
                    cout << ++res << '\n';
                    break;
                }
                else {
                    // 出队，耗时，队头下标后移
                    q.pop();
                    ++res;
                    ++leader_index;
                }
            }
        }
    }
}

int main() {
    Solve1();
    Solve2();
    return 0;
}