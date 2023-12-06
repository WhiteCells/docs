#include <iostream>

template <class T>
class Queue {
private:
    struct QueueNode {
        T data;
        QueueNode* next;
        QueueNode() : data(0), next(nullptr) {};
        QueueNode(T data) : data(data), next(nullptr) {}
        QueueNode(T data, QueueNode* next) : data(data), next(next) {}
    };
    QueueNode* front;
    QueueNode* rear;
public:
    Queue() {
        front = new QueueNode();
        rear = front;
    }
    Queue(const Queue& q) {

    }
    ~Queue() {

    }

    bool Push(T e) {

    }

    bool Pop() {

    }

    T Front() {

    }

    T Rear() {

    }
};


int main() {
    return 0;
}