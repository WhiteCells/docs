#include <iostream>
#include <string>
#include <queue>
#include <deque>

using namespace std;

int main() {
    int T; // 测试案例数
    cin >> T;
    while (T--) {
        deque<int> ready_queue; // 就绪队列
        queue<int> block_queue; // 阻止队列
        int n, t1, t2, t3, t4, t5, Q;
        // n-程序数、t1-赋值、t2-打印、t3-加锁、t4-解锁、t5-结束、Q-运行程序分配时间
        cin >> n >> t1 >> t2 >> t3 >> t4 >> t5 >> Q;
        vector<string> program[n]; // 存储指令
        for (int i = 0; i < n; ++i) {
            string s;
            while (getline(cin, s)) {
                if (s.empty()) {
                    continue;
                }
                program[i].push_back(s);
                if (s == "end") {
                    break;
                }
            }
            // 程序序号 i 放到 就绪队列
            ready_queue.push_back(i);
        }
        int program_index[n] = {}; // 存储当前程序执行到第几行
        int val[26] = {}; // 存储变量 a~z 的数据
        bool locked = false; // 锁的状态
        while (!ready_queue.empty()) {
            int times = 0; // 计算程序 i 耗时
            bool locked_fail = false; // 加锁是否失败
            bool program_end = false; // 程序是否结束
            // 当前耗时小于分配时间 继续读取指令
            while (times < Q) {
                // 取出指令
                int front_index = ready_queue.front(); // 当前需要执行程序的序号
                string instruct = program[front_index][program_index[front_index]];
                // 判断指令
                if ("end" == instruct) {
                    program_end = true;
                    break;
                }
                else if ("unlock" == instruct) {
                    // 阻止队列队头放入就绪队列队头，(阻止队列需要有数据)
                    if (!block_queue.empty()) {
                        ready_queue.push_front(block_queue.front());
                        block_queue.pop();
                    }
                    // 更新耗时
                    times += t4;
                    // 更新锁的状态
                    locked = false;
                    // 更新当前程序命令行位置下标
                    program_index[front_index]++;
                }
                else if ("lock" == instruct) {
                    // 如果程序已被加锁
                    if (true == locked) {
                        // 则加锁失败，直接将当前程序序号放入阻止队列，并弹出就绪队列队头
                        block_queue.push(ready_queue.front());
                        ready_queue.pop_front();
                        locked_fail = true;
                        program_index[front_index]++;
                        break;
                    }
                    // 更新耗时
                    times += t3;
                    // 修改锁定的状态
                    locked = true;
                    // 更新当前程序命令行位置下标
                    program_index[front_index]++;
                }
                else if ("print" == string(instruct.begin(), instruct.begin() + 5)) {
                    // 通过 val 数组找到需要打印的数据
                    std::cout << front_index + 1 << ": " << val[instruct[6] - 'a'] << '\n';
                    // 更新耗时
                    times += t2;
                    // 更新当前程序命令行位置下标
                    program_index[front_index]++;
                }
                else { // 赋值语句
                    // 计算赋值数字，并更新 val 数组
                    int num = 0;
                    for (int i = 4; i < instruct.size(); ++i) {
                        num = num * 10 + (instruct[i] - '0');
                    }
                    val[instruct[0] - 'a'] = num;
                    // 更新耗时
                    times += t1;
                    // 更新当前程序命令行位置下标
                    program_index[front_index]++;
                }
            }
            // 程序结束
            if (program_end) {
                ready_queue.pop_front();
                continue;
            }
            // 超时，成功加锁，就绪队列队头程序序号放到队尾
            if (!locked_fail) {
                ready_queue.push_back(ready_queue.front());
                ready_queue.pop_front();
            }
        }
    }
    return 0;
}