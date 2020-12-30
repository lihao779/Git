#pragma once
#include <iostream>
using namespace std;

template <class T>
struct BSTNode
{
    BSTNode(const T& val = T())
        :left(NULL)
         ,right(NULL)
         ,date(val)
    {}

    BSTNode<T>* left;
    BSTNode<T>* right;
    T date;
};


template <class T>
class BSTree
{
    typedef BSTNode<T> Node; 
    public:
    BSTree()
        :root(NULL)
    {}
    
    ~BSTree()
    {
        _Destroy(root);
    }

    Node* Find(const T& date)
    {
        Node* cur = root;
        /*
        while(cur && cur->date != date)
        {
            if(cur->date > date)
                cur = root->left;
            else
                cur = root->right;
        }
        return cur;
        */
        while(cur)
        {
            if(cur->date == date)
                break;
            else if(cur->date > date)
            {
                cur = cur->left;
            }
            else 
                cur = cur->right;
        }
        return cur;
    }

    bool Insert(const T& date)
    {
        if(root == NULL)
        {
            root = new Node(date);
            return true;
        }
        // 找待插入节点位置
        
        Node* cur = root;
        Node* parent = NULL;
        while(cur)
        {
            parent = cur;
            if(cur->date > date)
            {
                cur = cur->left;
            }
            else if(cur->date < date)
            {
                cur = cur->right;
            }
            else
                return false;
        }

        // 插入
        if(parent->date > date)
        {
            parent->left = new Node(date);
        }
        else
            parent->right = new Node(date);
        return true;

    }
    
    void InOrder()
    {
        _InOrder(root);
        cout<<endl;
    }
    
    bool Earse(const T& date)
    {
        if(!root)
            return false;
        Node* cur = root;
        Node* parent = NULL;
        while(cur)
        {
            if(cur->date == date)
                break;
            else if(cur->date > date)
            {
                parent = cur;
                cur = cur->left;
            }
            else
            {
                parent = cur;
                cur = cur->right;
           }
        }
        //值为date元素不存在
        if(!cur)
            return false;
        if(cur->left == NULL)
        {
            //只有右孩子or叶子节点
            if(!parent)
                root = cur->right;
            else if(cur == parent->left)
                parent->left = cur->right;
            else 
                parent->right = cur->right;
        }
        else if(cur->right == NULL)
        {
            //只有左孩子
            if(!parent)
                root = cur->left;
            else if(cur == parent->left)
                parent->left = cur->left;
            else
                parent->right = cur->left;
        }
        else
        {
            parent = cur;
            Node* del = cur->left;
            while(del->right)
            {
                parent = del;
                del = del->right;
            }
            cur->date = del->date;
            if(del == parent->right)
            {
                parent->right = del->left;
            }
            else
            {
               parent->left = del->left; 
            }
            cur = del;
        }
        delete cur;
        return true;

    }


    private:
    void _InOrder(Node* pRoot)
    {
        /*
        if(pRoot)
        {
            _InOrder(pRoot->left);
            cout<<pRoot->date<<" ";
            _InOrder(pRoot->right);
        }
        */
        if(!pRoot)
            return ;
        _InOrder(pRoot->left);
        cout<<pRoot->date<<" ";
        _InOrder(pRoot->right);
    }
    void _Destroy(Node*& pRoot)
    {
        if(!pRoot)
            return;
        _Destroy(pRoot->left);
        _Destroy(pRoot->right);
        delete pRoot;
        pRoot = NULL;
    }
    private:
    Node* root;
};


void Test()
{
    int array[] = {5,3,4,1,7,8,2,6,0,9};
    BSTree<int> t;
    for(auto e:array)
    {
        t.Insert(e);
    }
    t.InOrder();
    t.Earse(6);
    t.InOrder();
    t.Earse(8);
    t.InOrder();
    t.Earse(5);
    t.InOrder();
}
