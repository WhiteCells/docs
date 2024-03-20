#include <iostream>
#include <string>
using namespace std;

struct Stack {
    char arr[20];
    int top;
};

string Solve(string& str) {
    Stack s;
    s.top = 0;
    for (const auto& c : str) {
        if ('(' == c) {
            s.arr[s.top++] = '(';
        }
        else if (')' == c) {
            if (s.top <= 0) {
                return "NO";
            }
            --s.top;
        }
    }
    if (!s.top) {
        return "YES";
    }
    else {
        return "NO";
    }
}

int main() {
    // string str = "2*(x+y)/(1-x)@";
    // string str = "(25+x)*(a*(a+b+b)@";
    // cout << Solve(str);

    char c;
    Stack s;
    while (cin >> c && c != '@') {
        if ('(' == c) {
            s.arr[s.top++] = '(';
        }
        else if (')' == c) {
            if (!s.top) {
                cout << "NO" << '\n';
                return 0;
            }
            else {
                --s.top;
            }
        }
    }
    if (!s.top) {
        cout << "YES" << '\n';
    }
    else {
        cout << "NO" << '\n';
    }
    return 0;
}