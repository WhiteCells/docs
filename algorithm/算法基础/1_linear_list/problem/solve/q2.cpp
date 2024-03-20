#include <iostream>
#include <list>
#include <string>

using namespace std;

list<char> text;
int n = 0;

void Solve(string s) {
    list<char>::iterator it = text.begin();
    for (const auto c : s) {
        if ('[' == c) {
            it = text.begin();
        }
        else if (']' == c) {
            it = text.end();
        }
        else {
            it = text.insert(it, c);
            ++it;
        }
    }
}

void Print() {
    auto it = text.begin();
    string s;
    for (; it != text.end(); ++it) {
        s += *it;
    }
    cout << s << '\n';
}

int main() {
    cin >> n;
    while (n--) {
        string s;
        cin >> s;
        Solve(s);
        Print();
    }
    return 0;
}