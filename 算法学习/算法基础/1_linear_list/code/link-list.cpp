#include <iostream>

template <class T>
class List{
private:
    struct ListNode{
        T val;
        ListNode* next;
        ListNode(): val(0), next(nullptr){}
        ListNode(T val): val(val), next(nullptr){}
        ListNode(T val, ListNode* next): val(val), next(next){}
    };
    ListNode* head;
    int size;
public:
    List(){
        this->head = new ListNode(0);
        this->size = 0;
    }
    List(const List<T>& ls){
        if(!ls.head){
            this->head = nullptr;
            this->size = 0;
            return;
        }
        this->head = new ListNode();
        this->size = 0;
        ListNode* cur = this->head;
        ListNode* ls_cur = ls.head->next;
        while(ls_cur){
            ListNode* new_node = new ListNode(ls_cur->val);
            if(!new_node){
                return;
            }
            cur->next = new_node;
            ++this->size;
            ls_cur = ls_cur->next;
            cur = cur->next;
        }
    }
    ~List(){
        ListNode* cur = this->head;
        while(cur){
            ListNode* tmp = cur->next;
            delete cur;
            --this->size;
            cur = tmp;
        }
        cur = nullptr;
    }

    // pos 之前插入元素
    bool Insert(int pos, T val){
        if(pos < 1 || pos > this->size + 1){
            return false;
        }
        ListNode* cur = head;
        while(--pos){
            cur = cur->next;
        }
        ListNode* new_node = new ListNode(val, cur->next);
        if(!new_node){
            return false;
        }
        cur->next = new_node;
        ++this->size;
        return true;
    }

    int Size(){
        return this->size;
    }

    void Print(){
        ListNode* cur = head->next;
        while(cur){
            std::cout << cur->val << ' ';
            cur = cur->next;
        }
        std::cout << '\n';
    }
};

int main(){
    List<char> ls;
    ls.Insert(1, 65);
    ls.Insert(1, 66);
    ls.Insert(1, 67);
    ls.Print();
    std::cout << ls.Size() << '\n';

    List<char> ls2(ls);
    std::cout << ls2.Size() << '\n';
    ls2.Print();
    std::cout << ls2.Size() << '\n';
    std::cout << ls.Size() << '\n';
    return 0;
}