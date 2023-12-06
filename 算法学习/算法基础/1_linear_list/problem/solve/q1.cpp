#include <iostream>
#include <vector>

using namespace std;

int n = 0;
vector<int> block[25]; // 0 < n < 25

void Init() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        block[i].push_back(i);
    }
}

// 找到 val 所在的块 p 以及高度 h
void FindPosition(int val, int& p, int& h) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < block[i].size(); ++j) {
            if (block[i][j] == val) {
                p = i;
                h = j;
                return;
            }
        }
    }
}

// 块 p 中高度大于 h 的所有块归位
void Goback(int p, int h) {
    for (int i = h + 1; i < block[p].size(); ++i) {
        block[block[p][i]].push_back(block[p][i]);
    }
    block[p].resize(h + 1);
}

// 块 p 中高度大于等于 h 的所有块移动到块 q 上
void Moveall(int p, int h, int q) {
    for (int i = h; i < block[p].size(); ++i) {
        block[q].push_back(block[p][i]);
    }
    block[p].resize(h);
}

void Solve() {
    int a, b;
    string s1, s2;
    Init();
    while (cin >> s1) {
        if (s1 == "quit") {
            break;
        }
        cin >> a >> s2 >> b;
        int ap, ah; // a 所在的块，及高度
        int bp, bh; // b 所在的块，及高度
        FindPosition(a, ap, ah);
        FindPosition(b, bp, bh);
        if (ap == bp) {
            continue;
        }
        if (s1 == "move") { // a 归位
            Goback(ap, ah);
        }
        if (s2 == "onto") { // b 归位
            Goback(bp, bh);
        }
        Moveall(ap, ah, bp);
    }
}

void Print() {
    for (int i = 0; i < n; ++i) {
        cout << i << ":";
        for (int j = 0; j < block[i].size(); ++j) {
            cout << " " << block[i][j];
        }
        cout << '\n';
    }
}


int main() {
    Solve();
    Print();
    return 0;
}


