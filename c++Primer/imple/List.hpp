#include <iostream>
template<class T>
struct ListNode
{
    ListNode(const T& x = T()): left(nullptr), right(nullptr), data(x){}
    ListNode* left;
    ListNode* right;
    T data;
};  

template<class T>
class List
{
    typedef ListNode<T> Node;
    public:
        List() { CreateHead(); }

        List(size_t n, const T& data)
        {
            CreateHead();
            for(size_t i = 0; i < n; i++)
                push_back(data);
        }
        template<class InputIterator>
        List(InputIterator first, InputIterator last)
        {
            CreateHead();
            while(first != last)
                push_back(*first++);
        }
        List(List<T>& l)
        {
            CreateHead();
            auto it = l.head->left;
            while(it != l.head)
                push_back(*it++);
        }
        ~List()
        {
            clear();
            delete head;
        }
        List<T>& operator=(const List<T>& l)
        {
            if(&l != this)
            {
                //TODO
            }
            return *this;
        }
        void clear()
        {
            while(head->left != head)
            {
                auto it = head->left;
                head->left = it->left;
                it->left->right = head;
                delete it;
            }
        }
        void push_back(const T& data)
        {
            Node* cur = new Node(data);
            auto it = head->left;
            cur->left = it;
            cur->right = head;
            it->right = cur;
            head->left = cur;
        }
        //void pop_back()

    private:
        void CreateHead()
        {
            head = new Node;
            head->left = head;
            head->right = head;
        }
    private:
        Node* head;
};
