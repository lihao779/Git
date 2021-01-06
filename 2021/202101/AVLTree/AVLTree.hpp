#pragma once

template<class T>
struct AVLTreeNode
{
    AVLTreeNode(const T& x)
        :left(nullptr)
         ,right(nullptr)
         ,parent(nullptr)
         ,date(x)
         ,bf(0)
    {}

    AVLTreeNode<T>* left;
    AVLTreeNode<T>* right;
    AVLTreeNode<T>* parent;
    T date;
    int bf;
};

template<class T>
class AVLTree
{
    typedef AVLTreeNode<T> Node;
    public:
        AVLTree()
            :_root(nullptr)
        {}
        ~AVLTree()
        {}

        bool Insert(const T& date)
        {
            if(_root == nullptr)
            {
                _root = new Node(date);
                return true;
            }

            //找位置
            //插入节点
            Node* cur = _root;
            Node* parent = nullptr;
            while(cur)
            {
                parent = cur;
                if(cur->date > date)
                    cur = cur->left;
                else if(cur->date < date)
                    cur = cur->right;
                else
                    return false;
            }
            //插入新节点
            cur = new Node(date);
            if(date < parent->date)
                parent->left = cur;
            else
                parent->right = cur;
            cur->parent = parent;
            
            //更新双亲平衡因子
            while()
            {
                if(parent->left == cur)
                    parent->bf--;
                else
                    parent->bf++;

                if(parent->bf == 0)
                    return true;
                else if(parent->bf == 1 || parent->bf == -1)
                {
                   cur = cur->parent;
                   parent = cur->parent;
                }
                else
                {
                    //平衡因子是2 || -2
                    if(parent->bf == 2)
                    {
                        if(cur->bf == 1)
                        {
                            RotatoLeft(parent);
                        }
                    }
                    else
                    {
                        if(cur->bf == -1)
                        {
                            RotatoRight(parent);
                            return true;
                        }

                    }

                }
            }  

            return true;
        }
        void RotatoLeft(Node* parent)
        {
            Node* grandfather = parent->parent;
            Node* subR = parent->right;
            Node* subRL = subR->left;

            parent->right = subRL;
            if(subRL)
                subRL->parent = parent;
            subR->left = parent;
            parent->parent = subR;
            subR->parent = grandfather; 
            if(grandfather == nullptr)
                _root = subR;
            else
            {
                if(grandfather->left == parent)
                    grandfather->left = subR;
                else
                    grandfather->right = subR;
            }
            subR->bf = parent->bf =0;

        }
        void RotatoRight(Node* parent)
        {
            Node* grandfather = parent->parent;
            Node* subL = parent->left;
            Node* subLR = subL->right;

            parent->left = subLR;
            if(subLR)
                subLR->parent = parent;
            subL->right = parent;
            parent->parent = subL;
            subL->parent = grandfather;
            if(grandfather == nullptr)
                _root = subL;
            else
            {
                if(parent == grandfather->left)
                    grandfather->left = subL;
                else
                    grandfather->right = subL;
            }
            subL->bf = parent->bf = 0;
        }

    private:
        Node* _root;
        
};
