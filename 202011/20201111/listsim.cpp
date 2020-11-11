#include<iostream>

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
class List
{
    typedef ListNode<T> Node;
    public:
        List()
        {
            CreatHead();
        }

        List(size_t n,const T& date = T())
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
        List(const List<T>& L)
        {
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
            return head->next;
        }
        iterator end()
        {
            return head;
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
           return *begin;
       }
       T& front()
       {
           return *begin;
       }
       T& back()
       {
            return *(--end);
       }
       const T& back()const
       {
            return *(--end);
       }
        //////////////////
        //
        void push_back(T& date);
        void pop_back();
        void push_front(T& date);
        void pop_front();
        void insert(iterator pos,T& date);
        void erase(iterator pos);
        void clear();
        void swap();
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
