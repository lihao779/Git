#pragma once
#include <iostream>
using namespace std;

template<class K,class V>
struct BSTNode
{
    BSTNode(const K& k = K(),const V& v = V())
        :left(NULL)
         ,right(NULL)
         ,key(k)
         ,val(v)
    {}
    BSTNode<K,V>* left;
    BSTNode<K,V>* right;
    K key;
    V val;
};



template<class K,class V>
class BSTree
{
    typedef BSTNode<K,V> Node;
    public:
        BSTree()
            :root(NULL)
        {}
        Node* Find(const K& key)
        {
            if(root == NULL)
                return NULL;
            Node* cur = root;
            while(cur)
            {
                if(cur->key == key)
                    return cur;
                else if(cur->key > key)
                    cur = cur->right;
                else
                    cur = cur->left;
            }
            return NULL;
        }
        bool Insert(const K& key,const V& v)
        {
            if(root == NULL)
            {
                root = new Node(key,v);
                return true;
            }
            Node* cur = root;
            Node* parent = NULL; 
            while(cur)
            {
                parent = cur;
                if(cur->key == key)
                {
                    cur->val++;
                    return true;
                }
                else if(cur->key > key)
                {
                    cur = cur->left;
                }
                else
                {
                    cur = cur->right;
                }
            }
            if(key < parent->key)
                parent->left = new Node(key,v);
            else
                parent->right = new Node(key,v);
            return true;

        }
        void InOrder()
        {
            _InOrder(root);
        }
    private:
        void _InOrder(Node* root)
        {
            if(root)
            {
                _InOrder(root->left);
                cout<<root->key <<" "<<root->val<<endl;
                _InOrder(root->right);
            }
        }
    private:
        Node* root;
};

void TestString()
{
    string s[] = {"111","222","333","222"};
    BSTree<string,int> t;
    for(auto e: s)
    {
        t.Insert(e,1);
    }
    t.InOrder();
}




/*
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
        //
        //while(cur && cur->date != date)
        //{
        //    if(cur->date > date)
        //        cur = root->left;
        //    else
        //        cur = root->right;
        //}
        //return cur;
        
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
        
        //if(pRoot)
        //{
        //    _InOrder(pRoot->left);
        //    cout<<pRoot->date<<" ";
        //    _InOrder(pRoot->right);
        //}
       /
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





*/
