#include <iostream>
#include <stack>

using namespace std;

int main() {
    int n = 0;
    while (cin >> n && n != 0) {
        int B[n + 1];
        while (1) {
            cin >> B[1];
            if (!B[1]) {
                break;
            }
            for (int i = 2; i <= n; ++i) {
                cin >> B[i];
            }
            stack<int> s;
            int i = 1, j = 1;
            while (i <= n) {
                if (i == B[j]) {
                    ++i;
                    ++j;
                }
                else {
                    s.push(i);
                    ++i;
                }
                while (!s.empty() && s.top() == B[j]) {
                    ++j;
                    s.pop();
                }
            }
            if (j <= n) {
                cout << "No" << '\n';
            }
            else {
                cout << "Yes" << '\n';
            }
        }
        cout << '\n';
    }
    return 0;
}