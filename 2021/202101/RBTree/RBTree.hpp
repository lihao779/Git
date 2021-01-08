#pragma once

enum Color{RED,BLACK};

template<class T>
struct RBTreeNode
{
    RBTreeNode(const T& x = T(),Color c = RED)
        :left(nullptr)
         ,right(nullptr)
         ,parent(nullptr)
         ,color(c)
         ,date(x)
    {}
    RBTreeNode<T>* left;
    RBTreeNode<T>* right;
    RBTreeNode<T>* parent;
    
    Color color;
    T date;

};

template<class T>
class RBTree
{
    typedef RBTreeNode<T> Node;
    RBTree()
    {
        head = new Node();
        head->left = head;
        head->right = head;
    }
    bool Insert(const T& date)
    {
        Node*& root = GetRoot();
        if(root == nullptr)
        {
            root = new Node(date,BLACK);
            head->left = root;
            head->right = root;
            head->parent = root;
            root->parent = head;
            return true;
        }
        Node* cur = root;
        Node* parent = head;
        while(cur)
        {
            parent = cur;
            if(date < cur->date)
                cur = cur->left;
            else if(date > cur->date)
                cur = cur->right;
            else
                return false;
        }
        cur = new Node(date);
        if(date < parent->date)
            parent->left = cur;
        else
            parent->right = cur;
        cur->parent = parent;
        // 新节点插入后 由于新节点默认颜色是红色-
        // 如果parent节点的颜色是黑色--红黑树的性质没有遭到破坏
        // 如果parent节点的颜色是红色的--红黑树性质三-不能有两个连在一起的红色节点遭到破坏--需要调整
        
        while(parent->color == RED && parent != head)
        {
            Node* grandfater = parent->parent;
            if(parent == grandfater->left)
            {
                Node* uncle = grandfater->right;
                if(uncle && uncle->color == RED)
                {
                    uncle->color = BLACK;
                    parent->color = BLACK;
                    grandfater->color = RED;
                    
                    //继续往上更新
                    cur = grandfater;
                    parent = cur->parent;
                }
                else
                {
                    if(cur == parent->right)
                    {
                        RotateLeft(parent);/////////////
                        swap(cur,parent);/////////////
                    }
                    parent->color = BLACK;
                    grandfater->color = RED;
                    RotateRight(grandfater);
                }
                
            }
            else
            {
                Node* uncle = parent->left;
                if(uncle && uncle->color == RED)
                {
                    uncle->color = BLACK;
                    parent->color = BLACK;
                    grandfater->color = RED;
                    
                    //继续往上更新
                    cur = grandfater;
                    parent = cur->parent;
                }
                else
                {
                    if(cur == parent->left)
                    {
                        RotateRight(parent);
                        swap(parent,cur);
                    }
                    parent->color = BLACK;
                    grandfater->color = RED;
                    RotateLeft(grandfater);
                }

            }

        }
        


        root->color = BLACK;
        head->left = LeftMost();
        head->right = RightMost();
        return true;
    }
    
    private:
    void RotateLeft(Node* parent)
    {
        Node* grandfater = parent->parent;
        Node* subR = parent->right;
        Node* subRL = subR->left;
        
        parent->right = subRL;
        if(subRL)
            subRL->parent = parent;
        subR->left = parent;
        parent->parent = subR;
        subR->parent = grandfater;

    }
    void RotateRight(Node* parent)
    {
        Node* grandfater = parent->parent;
        Node* subL = parent->left;
        Node* subLR = subL->right;

        parent->left = subLR;
        if(subLR)
            subLR->parent = parent;
        subL->right = parent;
        parent->parent = subL;
        subL->parent = grandfater;
    }

    void swap(Node*& left,Node*& right)
    {
        Node* tmp = left;
        left = right;
        right = tmp;
    }
    Node* LeftMost()
    {
        Node* cur = GetRoot();
        if(cur == nullptr)
            return head;
        while(cur->left)
            cur = cur->left;
        return cur;
    }
    Node* RightMost()
    {
        Node* cur = GetRoot();
        if(cur == nullptr)
            return head;
        while(cur->right)
            cur = cur->right;
        return cur;
    }

    Node*& GetRoot()
    {
        return head->parent;
    }

    private:
        Node* head;
};
