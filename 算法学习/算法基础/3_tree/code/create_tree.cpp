#include <iostream>
using namespace std;

template <class T>
class TreeNode {
public:
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(val) : val(val), left(nullptr), right(nullptr) {}
    TreeNode(val, left, right) : val(val), left(left), right(right) {}
    ~TreeNode() {

    }
private:
    T val;
    TreeNode<T> *left;
    TreeNode<T> *right;
};

void CreateTree(TreeNode<int> &root) {

}

int main() {

    return 0;
}