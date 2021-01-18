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

template<class T>
class RBTree
{
    typedef RBTreeNode<T> Node;
    public:
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
        return true;
    }
    ~RBTree()
    {
        _Destroy(head->parent);
    }
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
        }
    }
    private:
        Node* head;
};


void TestRBTree()
{
    int array[] = {5,3,4,1,7,8,2,4,0,9};
    RBTree<int> t;
    for(auto e:array)
    {
       t.Insert(e); 
    }
    t.InOrder();
    if(t.IsValidRBTree())
    {
        cout<<"红黑树ok"<<endl;
    }
}
