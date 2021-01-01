#include<iostream>
#include<algorithm>

using namespace std;

template<class T>
struct ListNode
{
    ListNode(const T& value = T())
         :next(nullptr)
         ,prev(nullptr)
         ,date(value)
    {}
    ListNode<T>* next;
    ListNode<T>* prev;
    T date;
};


template<class T>
struct ListIterator
{
    typedef ListNode<T> Node;
    typedef ListIterator Self;
    public:
    ListIterator( Node* ptr = nullptr)
        :_ptr(ptr)
    {}
     
    ListIterator(const Self& s)
    {
        _ptr = s._ptr;
    }
    T& operator*()
    {
        return _ptr->date;
    }
    T* operator->()
    {
        return &_ptr->date;
    }
    Self& operator++()
    {
        _ptr=_ptr->next;
        return *this;
    }
    Self operator++(int)
    {
        Self temp(*this);
        _ptr=_ptr->next;
        return temp;
    }
    Self& operator--()
    {
        _ptr=_ptr->prev;
        return *this;
    }
    Self operator--(int)
    {
        Self temp(*this);
        _ptr=_ptr->prev;
        return temp;
    }
    ///////////////
    //比较
    bool operator!=(const Self& s)const
    {
        return _ptr!= s._ptr;
    }
    bool operator==(const Self& s)const
    {
        return _ptr==s._ptr;
    }
    Node* _ptr; 
};

template<class T,class Iterator>
struct ListReverseIterator
{
    typedef ListReverseIterator<T,Iterator> Self;
    typedef ListNode<T> Node;
    ListReverseIterator(Node* pNode = nullptr)
        :_it(pNode)
    {}
    
    T& operator*()
    {
        Iterator temp(_it);
        --temp;
        *temp;
    }
    T* operator->()
    {
        return &(*_it);
    }
    Self& operator++()
    {
        --_it;
        return *this;
    }
    Self operator++(int)
    {
        _it--;
        return *this;
    }
    Self& operator--()
    {
        ++_it;
        return *this;
    }
    Self operator--(int)
    {
        _it++;
        return *this;
    }
    bool operator==(const Self& s)
    {
        return _it._ptr==s._ptr;
    }

    bool operator!=(const Self& s)
    {
        return _it._ptr!=s._ptr;
    }
    Iterator _it;

};


template<class T>
class List
{
    typedef ListNode<T> Node;
    typedef ListIterator<T> iterator;
    public:
        List()
        {
            CreatHead();
        }

        List(int  n,const T& date = T())
        {
            CreatHead();
            for(size_t i = 0;i < n;++i)
            {
                push_back(date);
            }
        }
        template<class Iterator>
        List(Iterator first,Iterator last)
        {
            CreatHead();
            while(first!=last)
            {
                push_back(*first);
                ++first;
            }
        }
        List( List<T>& L)
        {
            CreatHead();
            auto it = L.begin();
            while(it!=L.end())
            {
                push_back(*it);
                ++it;
            }
        }

        ~List()
        {
            clear();
            delete head;
            head = nullptr;
        }
        
        ///////////////////////////////////
        //iterator
        iterator begin()
        {
            return iterator(head->next);
        }
        iterator end()
        {
            return iterator(head);
        }

        //////////////////////////
        //capacity
        size_t size()
        {
            size_t count = 0;
            auto it = begin();
            while(it!=end())
            {
                count++;
                ++it;
            }
            return count;
        }
        bool empty()
        {
            return head->next = head;
        }
        void resize(size_t newsize,const T& date = T())
        {
            size_t oldsize = size();
            if(newsize<oldsize)
            {
                for(size_t i = newsize;i<oldsize;++i)
                {
                    pop_back();
                }
            }
            else
            {
                for(size_t i = oldsize;i<newsize;++i)
                {
                    push_back(date);
                }
            }

        }
       ////////////////////////
       //access
       const T& front()const
       {
           return *begin();
       }
       T& front()
       {
           return *begin();
       }
       T& back()
       {
            return *(--end());
       }
       const T& back()const
       {
            return *(--end());
       }
        //////////////////
        //
        void push_back(T date)
        {
            insert(end(),date);
        }
        void pop_back()
        {
            erase(--end());
        }
        void push_front(T& date)
        {
            insert(begin(),date);
        }
        void pop_front()
        {
            erase(begin());
        }
        iterator insert(iterator pos,const T& date)
        {
            Node* cur = new Node(date);
            cur->next = pos._ptr;
            cur->prev = pos._ptr->prev;
            pos._ptr->prev = cur;
            cur->prev->next = cur;
            return iterator(cur);
        }
        iterator erase(iterator pos)
        {
            Node* cur = pos._ptr;
            Node* ret = pos._ptr->next;
            if(cur != head)
            {
                cur->next->prev = cur->prev;
                cur->prev->next = cur->next;
                delete cur;
            }
            return iterator(ret);
        }
        iterator erase(iterator first,iterator last)
        {
            while(first!=last)
            {
                first = erase(first);
            }
            return last;            
        }
        void clear()
        {
            erase(begin(),end());
        }
        void swap(List<T>& L)
        {
            std::swap(head,L.head);
        }
    private:
        void CreatHead()
        {
            head = new Node;
            head->next = head;
            head->prev = head;
        }
    private:
        Node* head;
};

void TestList1()
{
    List<int> L1;
    List<int> L2(3,10);
    cout<<L2.size()<<endl;
    for(auto e: L2)
    {
        cout<<e<<" ";
    }
    cout<<endl;
    int array[] = {1,2,3};
    List<int> L3(array,array+3);
    for(auto e: L2)
    {
        cout<<e<<" ";
    }
    cout<<endl;
}

void TestList2()
{
    List<int> L;
    L.push_back(1);
    L.push_back(2);
    L.push_back(3);
    L.push_back(4);
    L.push_back(5);
    cout<<L.front()<<endl;
    cout<<L.back()<<endl;
    L.resize(10,10);
    auto it = L.begin();
    while(it!=L.end())
    {
        cout<<*it<<" ";
        ++it;
    }
    cout<<endl;
    L.pop_back();
    L.pop_front();
    cout<<L.front()<<endl;
    cout<<L.back()<<endl;
    
    //好像不行
    //L.insert(find(L.begin(),L.end(),3),100);
    //L.erase(find(L.begin(),L.end(),100));
    L.clear();
    cout<<L.size()<<endl;

}
struct A
{
    int a;
    int b;
    int c;
};
void TestList3()
{
    List<A> L;
    A a{1,2,3};
    L.push_back(a);
    auto it = L.begin();
    it->a = 10;
}
int main()
{
    // TestList1();
    // TestList2();
    TestList3();
    return 0;
}
