#include<iostream>
using namespace std;

template<class T>
class queue
{   
    struct Node
    {
        T val;
        Node *later;
        Node(T _val)
        {
            val = _val;
            later = nullptr;
        }
    };

    Node *head;
    Node *tail;

public:
    queue()
    {
        head = new Node(T());
        tail = head;
    }
    ~queue()
    {
        while(head)
        {
            Node *t = head;
            head = head->later;
            delete t;
        }
        tail = nullptr;
    }

    bool pop()
    {
        if(head->later)
        {
            Node *del = head->later;
            head->later = del->later;
            if(head->later == nullptr)
            {
                tail = head;
            }
            delete del;
            return true;
        }
        return false;
    }

    T front()
    {
        return head->later->val;
    }

    void push(T val)
    {
        Node *newNode = new Node(val);
        tail->later = newNode;
        tail = newNode;
    }
};


int main()
{
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    cout << q.front() << endl;
    q.pop();
    cout << q.front() << endl;
    q.pop();
    cout << q.front() << endl;
    q.pop();
}
