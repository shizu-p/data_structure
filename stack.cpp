#include<iostream>

using namespace std;

template<class T>
class stack
{
    struct Node {
        T val;
        Node *under;
        Node(T _val){
            val = _val;
            under = nullptr;
        }
    };

    Node *top;
    Node *bottom;
public:
    stack()
    {
        bottom = new Node(T());
        top = bottom;
    }
    ~stack()
    {
        while(top)
        {
            Node *del = top;
            top = top->under;
            delete del;
        }
        bottom = nullptr;
    }

    T front()
    {
        return top->val;
    }

    void pop()
    {
        Node *del = top;
        top = top->under;
        delete del;
    }

    void push(T val)
    {
        Node *newNode = new Node(val);
        newNode->under = top;
        top = newNode;
    }
};


int main() 
{
    stack<int> st;
    st.push(1);
    st.push(2);
    cout << st.front() << endl;
    st.pop();
    cout << st.front() << endl;
    st.pop();
}
