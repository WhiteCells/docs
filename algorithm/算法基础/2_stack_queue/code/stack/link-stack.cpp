#include <iostream>

template <class T>
class Stack {
private:
    struct StackNode {
        T data;
        StackNode* next;
        StackNode() : data(0), next(nullptr) {}
        StackNode(T data) : data(data), next(nullptr) {}
        StackNode(T data, StackNode* next) : data(data), next(next) {}
    };
    StackNode* head;
    int size;
public:
    Stack() {
        this->head = new StackNode();
        this->size = 0;
    }
    Stack(const Stack<T>& s) {
        if (s.Empty()) {
            return;
        }
        this->head = new StackNode();
        this->size = 0;
        StackNode* cur = this->head;
        StackNode* s_cur = s.head->next;
        while (s_cur) {
            StackNode* new_node = new StackNode(s_cur->data);
            if (!new_node) {
                return;
            }
            cur->next = new_node;
            ++this->size;
            cur = cur->next;
            s_cur = s_cur->next;
        }
    }
    ~Stack() {
        StackNode* cur = this->head;
        while (cur) {
            StackNode* tmp = cur->next;
            delete cur;
            --this->size;
            cur = tmp;
        }
    }

    bool Push(T e) {
        StackNode* new_node = new StackNode(e, this->head->next);
        if (!new_node) {
            return false;
        }
        this->head->next = new_node;
        ++this->size;
        return true;
    }

    bool Pop() {
        if (!this->head->next) {
            return false;
        }
        StackNode* tmp = this->head->next;
        this->head->next = tmp->next;
        delete tmp;
        --this->size;
        return true;
    }

    T Top() {
        if (!this->head->next) {
            return -1;
        }
        return this->head->next->data;
    }

    int Size() const {
        return this->size;
    }

    bool Empty() const {
        return !this->Size();
    }
};

int main() {
    Stack<int> s;
    s.Push(1);
    s.Push(2);
    s.Push(4);
    s.Push(3);

    s.Pop();

    std::cout << s.Empty() << '\n';
    std::cout << s.Top() << '\n';
    std::cout << s.Size() << '\n';

    Stack<int> s2(s);

    std::cout << s2.Top() << '\n';
    std::cout << s2.Size() << '\n';

    return 0;
}