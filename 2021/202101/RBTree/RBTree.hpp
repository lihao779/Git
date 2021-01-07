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





        //....
        //
        //
        head->left = LeftMost();
        head->right = RightMost();
        return true;
    }
    
    private:
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
