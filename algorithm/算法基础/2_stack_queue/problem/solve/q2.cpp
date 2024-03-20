#include <iostream>
#include <stack>
#include <string>

using namespace std;

struct Matrix {
    int m, n;
    Matrix(int m = 0, int n = 0) : m(m), n(n) {}
};


int main() {
    stack<Matrix> s;
    Matrix m[26];
    int n = 0;
    cin >> n;
    while (n--) {
        char c;
        cin >> c;
        cin >> m[c - 'A'].m >> m[c - 'A'].n;
    }
    string str;
    while (cin >> str) {
        bool error = false;
        int ans = 0;
        for (int i = 0; i < str.size(); ++i) {
            if ('A' <= str[i] && str[i] <= 'Z') {
                s.push(m[str[i] - 'A']);
            }
            else if (')' == str[i]) {
                // (m1*m2)
                Matrix m2 = s.top(); // 先取出 m2
                s.pop();
                Matrix m1 = s.top(); // 再取出 m1
                s.pop();
                if (m1.n != m2.m) {
                    error = true;
                    break;
                }
                ans += m1.m * m1.n * m2.n;
                s.push(Matrix(m1.m, m2.n));
            }
        }
        if (error) {
            cout << "error" << '\n';
        }
        else {
            cout << ans << '\n';
        }
    }
    return 0;
}