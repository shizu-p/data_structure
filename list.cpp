#include<iostream>
#include<cassert>
using namespace std;

template<class T>
class List
{
    struct Node{
        T val;
        Node *former;
        Node *latter;
        Node(T _val){
            val = _val;
            former = nullptr;
            latter = nullptr;
        }
    };

    Node *nil;
    
public:
    List(){
        nil = new Node(T());
        nil->latter = nil;
        nil->former = nil;
    }
    ~List(){
        Node *tmp = nil->latter;
        while(tmp!=nil){
            Node *del = tmp;
            tmp = tmp->latter;
            delete del;
        }
    }
    void push_front(T val){
        Node *newNode = new Node(val);
        newNode->latter = nil->latter;
        nil->latter->former = newNode;
        nil->latter = newNode;
        newNode->former = nil;
    }

    void push_back(T val){
        Node *newNode = new Node(val);
        newNode->former = nil->former;
        nil->former->latter = newNode;
        nil->former = newNode;
        newNode->latter = nil;
    }

    T pop_front(){
        assert(nil->latter != nil);
        T ret = nil->latter->val;
        nil->latter->latter->former = nil;
        Node *del = nil->latter;
        nil->latter = nil->latter->latter;
        delete del;
        return ret;
    }

    T pop_back(){
        assert(nil->former != nil);
        T ret = nil->former->val;
        nil->former->former->latter = nil;
        Node *del = nil->former;
        nil->former = nil->former->former;
        delete del;
        return ret;
    }

    void print(){
        Node *tmp = nil;
        while(tmp->latter != nil){
            cout << tmp->latter->val << endl;
            tmp = tmp->latter;
        }
    }
};

int main(){
    List<int> list;
    list.push_front(20);
    list.push_front(30);
    list.push_back(50);
    list.print();

    cout << endl;
    cout << "pop front " << list.pop_front() << endl;
    list.print();

    cout << endl;
    cout << "pop back " << list.pop_back() << endl;
    list.print();

    cout << list.pop_back() << endl;
}
