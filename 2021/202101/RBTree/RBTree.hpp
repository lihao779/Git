#pragma once
#include <iostream>
using namespace std;

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




//构造迭代器
template<class T>
struct RBTreeIterator
{
    typedef RBTreeNode<T> Node;
    typedef RBTreeIterator<T> Self;
    RBTreeIterator(Node* node = nullptr)
        :pNode(node)
    {}
    // 具有指针类似的方法
    T& operator*()
    {
        return pNode->date;
    }
    T* operator->()
    {
        return &(operator*());
    }

    Self& operator++()
    {
        Increament();
        return *this;
    }
    Self operator++(int)
    {
        Self temp(*this);
        Increament();
        return temp;
    }
    Self& operator--()
    {
        Decreament();
        return *this;
    }
    Self operator--(int)
    {
        Self temp(*this);
        Decreament();
        return temp;
    }
    bool operator!=(const Self& s)
    {
        return pNode != s.pNode;
    }
    bool operator==(const Self& s)
    {
        return pNode == s.pNode;
    }
    private:
    void Increament()
    {
        //分两种情况
        //1.有右子树
        //2.没有右子树
        if(pNode->right)
        {
            pNode = pNode->right;
            while(pNode->left)
                pNode = pNode->left;
        }
        else
        {
            Node* parent = pNode->parent;
            while(parent->right == pNode)
            {
                pNode = parent;
                parent = pNode->parent;
            }
            //特殊：如果根节点没有右子树
            if(pNode->right != parent)
            pNode = parent;
        }
    }
    void Decreament()
    {
        //分三种情况
        //1.pNode已经在end()的位置
        //2.有左子树
        //3.没有左子树
        if(pNode->parent->parent == pNode && pNode->color == RED)
            pNode = pNode->right;
        else if(pNode->left)
        {
            pNode = pNode->left;
            while(pNode->right)
                pNode = pNode->right;
        }
        else
        {
            Node* parent = pNode->parent;
            while(parent->left == pNode)
            {
                pNode = parent;
                parent = pNode->parent;
            }
            pNode = parent;
        }
    }
    Node* pNode;
};



template<class T,class KOFV>
class RBTree
{
    typedef RBTreeNode<T> Node;
    public:
    typedef RBTreeIterator<T> iterator;
    public:
    RBTree()
    {
        head = new Node();
        head->left = head;
        head->right = head;
        _size = 0;
    }

    pair<iterator,bool> Insert(const T& date)
    {
        Node*& root = GetRoot();
        if(root == nullptr)
        {
            root = new Node(date,BLACK);
            head->left = root;
            head->right = root;
            head->parent = root;
            root->parent = head;
            _size++;
            return make_pair(iterator(root),true);
        }
        Node* cur = root;
        Node* parent = head;
        KOFV kofv;
        while(cur)
        {
            parent = cur;
            if(kofv(date) < kofv(cur->date))
                cur = cur->left;
            else if(kofv(date) > kofv(cur->date))
                cur = cur->right;
            else
                return make_pair(iterator(cur),false);
        }
        cur = new Node(date);
        Node* pNewNode = cur;
        if(kofv(date) < kofv(parent->date))
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
                Node* uncle = grandfater->left;
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
        _size++;
        return make_pair(pNewNode,true);
    }
    
    void swap(RBTree<T,KOFV>& t)
    {
        std::swap(head,t.head);
        std::swap(_size,t._size);
    }
    
    void clear()
    {
        _Destroy(head->parent);
        _size= 0;
        head->left = head;
        head->right = head;
    }

    iterator find(const T& date)
    {
        KOFV kofv;
        Node* cur = GetRoot();
        while(cur)
        {
            if(kofv(cur->date) == kofv(date))
                return iterator(cur);
            else if(kofv(date) < kofv(cur->date))
                cur = cur->left;
            else
                cur = cur->right;
        }
        return end();
    }
    ~RBTree()
    {
        _Destroy(head->parent);
        delete head;
        head = nullptr;
    }

    ///////////////////////////
    //iterator
    iterator begin()
    {
        return iterator(head->left);
    }
    iterator end()
    {
        return iterator(head);
    }


    ///////////////////////////////
    // capacity
    bool empty()const 
    {
        return head->parent == nullptr;
    }

    size_t size()const
    {
        return _size;
    }
    ////////////////////////////
    //access

    void InOrder()
    {
        _InOrder(head->parent);
        cout<<endl;
    }
    
    /*
    bool IsValidRBTree()  //检测是否为红黑树
    {
        Node* root = GetRoot();
        //空树
        if(root == nullptr)
            return true;

        //非空--------按照红黑树的性质检测
        //性质二检测
        if(root->color != BLACK)
        {
            cout<<"违反红黑树的性质二!!!"<<endl;
            return false;
        }
        //性质三和四检测
        size_t blackCount = 0;
        Node* cur = root;
        while(cur)
        {
            if(cur->color == BLACK)
                blackCount++;
            cur = cur->left;
        }
        
        //检测其他路径黑色节点个数是否和最左侧节点个数是否相同
        size_t pathCount = 0;
        return _IsValidRBTree(root,blackCount,pathCount);

    }
    */
    bool IsValidRBTree()
    {
        Node* root = GetRoot();
        if(root == nullptr)
            return true;
        
        if(root->color != BLACK)
        {
            cout<<"违反红黑树性质2：根节点是黑色~~~"<<endl;
        }

        //检测红黑树性质三性质四
        size_t blackcount = 0;
        Node* cur = root;
        while(cur)
        {
            if(cur->color == BLACK)
            {
                blackcount++;
            }
            cur = cur->left;
        }

        size_t pathcount = 0;
        return _IsValidRBTree(root,blackcount,pathcount);
    }
    private:
    bool _IsValidRBTree(Node* root,size_t blackcount,size_t pathcount)
    {
        if(root->color == BLACK)
            pathcount++;
        Node* parent = root->parent;
        if(parent != head && parent->color == RED && root->color == RED)
        {
            cout<<"违反红黑树性质三：两个红色节点相连~~~"<<endl;
            return false;
        }
        if(root->left == nullptr || root->right == nullptr)
        {
            if(pathcount != blackcount)
            {
                cout<<"违反红黑树性质四：每条路径的黑色节点个数不同~~~"<<endl;
                return false;
            }
            return true;
        }
        return _IsValidRBTree(root->left,blackcount,pathcount) && _IsValidRBTree(root->right,blackcount,pathcount);
    }

    /*
    bool _IsValidRBTree(Node* root,size_t blackCount,size_t pathCount)
    {
        if(root == nullptr)
            return true;
        if(root->color == BLACK)
            pathCount++;
        
        Node* parent = root->parent;
        if(parent != head)
        {
            if(parent->color == RED && root->color == RED)
            {
                cout<<"违反红黑树性质三!!!"<<endl;
                return false;
            }
        }
        if(root->left == nullptr && root->right == nullptr )
        {
            if(pathCount != blackCount)
            {
                cout<<"违反红黑树性质四!!!"<<endl;
                return false;
            }
        }
        return _IsValidRBTree(root->left,blackCount,pathCount) && _IsValidRBTree(root->right,blackCount,pathCount);

    }
    */
    void _InOrder(Node* root)
    {
        if(root)
        {
            _InOrder(root->left);
            cout<<root->date<<" ";
            _InOrder(root->right);
        }
    }
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
        // 连接上面部分
        if(grandfater == head)
        {
            head->parent = subR;
        }
        else
        {
            if(grandfater->left == parent)
            {
                grandfater->left = subR;
            }
            else
            {
                grandfater->right = subR;
            }
        }

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
        // 连接上面部分
        if(grandfater == head)
        {
            head->parent = subL;
        }
        else
        {
            if(grandfater->left == parent)
            {
                grandfater->left = subL;
            }
            else
            {
                grandfater->left = subL;
            }
        }
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

    void _Destroy(Node*& root)
    {
        if(root)
        {
            _Destroy(root->left);
            _Destroy(root->right);
            delete root;
            root = nullptr;
            _size = 0;
        }
    }
    private:
        Node* head;
        size_t _size;
};




class KOFV
{
    public:
        int operator()(int v)
        {
            return v;
        }
};
void TestRBTree()
{
    int array[] = {5,3,4,1,7,8,2,4,0,9};
    RBTree<int,KOFV> t;
    for(auto e:array)
    {
       t.Insert(e); 
    }
    t.InOrder();
    if(t.IsValidRBTree())
    {
        cout<<"红黑树ok"<<endl;
    }
    for(auto e:t)
    {
        cout<<e<<" ";
    }
    cout<<endl;
    RBTree<int,KOFV>::iterator it = t.begin();
    while(it != t.end())
    {
        cout<<*it<<" ";
        it++;
    }
    cout<<endl;
}
