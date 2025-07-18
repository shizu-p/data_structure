#include<algorithm>

using namespace std;

template<class T>

class AVLTree
{
    struct Node
    {
        Node *par,*left,*right;
        T key;
        int height,size;

        Node(T x)
        {
            left = right = par = nullptr;
            height = 1;
            key = x;
            size = 1;
        }

        inline int factor() const 
        {
            // 高低差
            int lv = (this->left ? this->left->height : 0);
            int rv = (this->right ? this->right->height : 0);
            return (rv-lv);
        }
    
        inline int update_height()
        {
            return this->height = (
                (this->left ? this->left->heght : 0),
                (this->right ? this->right->height : 0)
            ) + 1;
        }

        inline bool is_left(Node *node) const 
        {
            return left == node;
        }

        inline void assign(Node *node)
        {
            this->key = node->key;
        }

        inline Node* rotate_left ()
        {
            Node *r = this->right , *m = r->left,*p = this->par;
            if(r->par = p)
            {
                if(p->left == this) p->left = r;
                else p->right = r;
            }
            if(this->right = m) m->par = this;
            r->left = this;
            this->par = r;

            int sz = this->size;
            this->size += (m ? m->size : 0) - r->size;
            r->size = sz;

            this->update_height();
            r->update_height();
            return r;
        }

        inline Node* rotate_right()
        {
            Node *l = this->left;
            Node *m = l->right;
            Node *p = this->par;
            if(l->par = p)
            {
                if(p->left == this) p->left = l;
                else p->right = l;
            }

            if(this->left = m) m->par = this;
            l->right = this;
            this->par = l;

            int sz = this->size;
            this->size += (m ? m->size : 0) - l->size;
            l->size = sz;

            this->update_height();
            l->update_height();
            return l;
        }

        inline Node* rotate_double_right()
        {
            Node *l = this->left;
            Node *p = this->par;
            Node *m = l->right;
            Node *ml = m->left;
            Node *mr = m->right;

            if((m->par = p))
            {
                if(p->left == this) p->left = m;
                else p->right = m;
            }
            if((l->right = ml)) ml->par = l;
            if((this->left = mr)) mr->par = this;
            m->left = l;
            l->par = m;
            m->right = this;
            this->par = m;

            int sz = this->size;
            this->size += (mr ? mr->size : 0) - l->size;
            l->size += (ml ? ml->size : 0) - m->size;
            m->size = sz;

            this->update_height();
            l->update_height();
            m->update_height();

            return m;
        }

        inline Node* rotate_double_left()
        {
            Node *r = this->right;
            Node *p = this->par;
            Node *m = r->left;
            Node *ml = m->left;
            Node *mr = m->right;
            if(m->par = p)
            {
                if(p->left == this) p->left = m;
                else p->right = m;
            }
            if(this->right = ml) ml->par = this;
            if(r->left = mr) mr->par = r;
            m->left = this;
            this->par = m;
            m->right = r;
            r->par = m;

            int sz = this->size;
            this->size += (ml ? ml->size : 0) - r->size;
            r->size += (mr ? mr->size : 0) - m->size;
            m->size = sz;

            this->update_height();
            r->update_height();
            m->update_height();

            return m;
        }
    };
    Node *root;

    inline Node* find_node(Node *node, T x)
    {
        if(node == nullptr) return nullptr;
        while(node->key != x)
        {
            if( x < node->key )
            {
                if(!node->left)break;
                node = node->left;
            }
            else
            {
                if(!node->right) break;
                node = node->right;
            }
        }
        return node;
    }

    inline void remove_node(Node *node)
    {
        T x = node->key;
        Node *par = node->par;

        if(!node->left || !node->right)
        {
            Node *n_node = (node->left ? node->left : node->right);
            if(par)
            {
                if(x < par->key)
                {
                    par->left = n_node;
                }
                else
                {
                    par->right = n_node;
                }
            }
            if((node = n_node)) node->par = par;
        }
        else
        {
            Node *c_node = find_node(node->right,x);
            *c_node = c_node->right;
            Node *c_par = c_node->par;
            if(node->right == c_node)
            {
                if((node->right = c_node)) c_node->par = c_par;
            }
            else
            {
                if((c_par->left = c_node)) c_node->par = c_par;
            }
            node->assign(c_node);
            node = c_node;
            par = c_par;
        }

        while(par)
        {
            --par->size;
            par->update_height();
            if(par->is_left(node))
            {
                if(par->factor() == 2)
                {
                    Node *sib = par->right;
                    if(sib->factor() < 0)
                    {
                        node = par->rotate_double_left();
                    }
                    else
                    {
                        node = par->rotate_left();
                    }
                }
                else
                {
                    if(par->factor() == 1) break;
                    node = par;
                }
                par = node->par;
            }
            else
            {
                if(par->factor() == -2)
                {
                    Node *sib = par->left;
                    if(sib->factor() > 0)
                    {
                        node = par->rotate_double_right();
                    }
                    else
                    {
                        node = par->rotate_right();
                    }
                }
                else
                {
                    if(par->factor() == -1)break;
                    node = par;
                }
                par = node->par;
            }
        }
        if(par)
        {
            node = par;
            par = par->par;
            while(par)
            {
                --par->size;
                par->update_height();
                node = par;
                par = node->par;
            }
        }

        this->root = node;
    }

public:
    AVLTree()
    {
        root = nullptr;
    }

    inline bool find(T x)
    {
        if(!this->root)
        {
            return false;
        }

        Node *node = find_node(this->root,x);
        return (node->key == x);
    }

    inline T at(int k)
    {
        if(!this->root)
        {
            return 0;
        }

        Node *node = this->root;
        ++k;
        while(1)
        {
            int l_size = (node->left ? node->left->size : 0) + 1;
            if(l_size == k)break;

            if(k<l_size)
            {
                node = node->left;
            }
            else
            {
                node = node->right;
                k -= l_size;
            }
        }
        return node->key;
    }

    inline bool insert(T x)
    {
        if(!this->root)
        {
            this->root = newNode(x);
            return true;
        }

        Node *node = find_node(this->root,x);
        if(node->key == x)
        {
            return false;
        }
        
        Node *new_node = new Node(x);
        new_node->par = node;
        if(x < node->key)
        {
            node->left = new_node;
        }
        else
        {
            node->right = new_node;
        }
        node = new_node;

        while(node->par)
        {
            Node *par = node->par;
            ++par->size;
            par->update_height();
            if(par->is_left(node))
            {
                if(par->factor() == -2)
                {
                    if(node->factor() > 0)
                    {
                        node = par->rotate_double_right();
                    }
                    else
                    {
                        node = par->rotate_right();
                    }
                }
                else
                {
                    if(par->factor() >= 0) break;
                    node = par;
                }
            }
            else
            {
                if(par->factor() == 2)
                {
                    if(node->factor() < 0)
                    {
                        node = par->rotate_double_left();
                    }
                    else
                    {
                        node = par->rotate_left();
                    }
                }
                else
                {
                    if(par->factor() <= 0) break;
                    node = par;
                }
            }
        }
        if(node->par)
        {
            node = node->par;
            Node *par = node->par;
            while(par)
            {
                ++par->size;
                par->update_height();
                node = par;
                par = node->par;
            }
        }
        this->root = node;
        return true;
    }

    inline bool remove(T x)
    {
        if(!this->root)
        {
            return false;
        }

        Node *node = find_node(this->root,x);
        if(node->key  != x)
        {
            return false;
        }

        remove_node(node);
        return true;
    }

    int size()
    {
        return (this->root ? this->root->size : 0);
    }
};

int main()
{
}
