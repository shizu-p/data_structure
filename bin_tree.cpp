#include<iostream>

using namespace std;

struct BinTree{
    struct Node {
        int key;
        Node *par,*left,*right;
        Node(int _key,Node* _par)
        :key(_key),par(_par),left(nullptr),right(nullptr)
        {}
    };

    Node *root;

    BinTree()
    {
        root = nullptr;
    }
    ~BinTree()
    {
        cl(root);
    }
    void insert(int val)
    {
        if(contains(val)) return;
        insert_r(val,root,nullptr);
    }

    Node* insert_r(int val,Node *cur,Node *prev)
    {
        if(!cur)
        {
            if(!prev)
            {
                return root = new Node(val,nullptr);
            }
            if(prev->key > val)
            {
                prev->left = new Node(val,prev);
                return prev->left;
            }
            else
            {
                prev->right = new Node(val,prev);
                return prev->right;
            }
        }

        if(cur -> key > val)
        {
            return insert_r(val,cur->left,cur);
        }
        else
        {
            return insert_r(val,cur->right,cur);
        }
    }

    void cl(Node *target)
    {
        if ( !target-> left && !target -> right)
        {
            delete target;
            return;
        }
        if(target->left) cl(target->left);
        if(target->right) cl(target->right);
        delete target;
    }
    
    void print()
    {
        print_r(root);
    }

    void print_r(Node *cur,int depth = 0)
    {
        if(!cur)return;
        print_r(cur->left,depth+1);
        print_r(cur->right,depth+1);
        cout << cur->key << " "<< depth << endl;
    }

    bool contains(int val)
    {
        return bool(search_r(val,root));
    }

    Node* search_r(int val,Node *cur)
    {
        if(!cur)
        {
            return nullptr;
        }
        
        if(cur->key == val)
        {
            return cur;
        }

        if(cur->key > val)
        {
            return search_r(val,cur->left);
        }
        else
        {
            return search_r(val,cur->right);
        }
    }
    
    // 消したいkeyの値を右部分木で一番小さい値に書き換える
    // https://www.momoyama-usagi.com/entry/info-algo-tree#2-7
    bool erase(int val)
    {
        Node *target = search_r(val,root);
        if(target)
        {
            return false;
        }

        // 対象が0個か一個しか子をもたないばあい
        if(target->left == nullptr || target->right == nullptr)
        {
            delete_node_helper(target);
            return true;
        }

        // 対象が2個子を持つ場合
        Node *u = search_min(target->right);
        target->key = u -> key;
        delete_node_helper(u);
        return true;

    }
    Node* search_min(Node *cur)
    {
        Node *prev = nullptr;
        while(cur)
        {
            prev = cur;
            cur = cur->left;
        }
        return prev;
    }

    Node* search_max(Node *cur)
    {
        Node *prev = nullptr;
        while(cur)
        {
            prev = cur;
            cur = cur->right;
        }
        return prev;
    }
    
    void delete_node_helper(Node *node_to_delete)
    {
        if(!node_to_delete)return;
        
        Node* child = (node_to_delete->left !=nullptr) ? 
            node_to_delete->left : node_to_delete->right;
        
        if(node_to_delete == root)
        {
            root = child;
            if(child)
            {
                child->par = nullptr;
            }
        }
        else
        {
            if(node_to_delete->par->left == node_to_delete)
            {
                node_to_delete->par->left = child;
            }
            else
            {
                node_to_delete->par->right = child;
            }

            if(child)
            {
                child->par = node_to_delete->par;
            }
        }

        delete node_to_delete;
    }
};

int main()
{
    BinTree tr;
    for(int i=0;i<10;++i){
        tr.insert(i+2*i);
        tr.insert(i-2*i);
    }
    tr.print();
    
    cout << endl;
    tr.erase(0);
    tr.print();
}
