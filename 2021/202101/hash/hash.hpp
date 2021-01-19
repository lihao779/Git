#pragma once
#include <vector>
#include <iostream>
using namespace std;




template<class T>
struct HashNode
{
    HashNode(const T& x = T())
    :next(nullptr)
     ,date(x)
    {}

    HashNode* next;
    T date;
};

template<class T>
class  HashBucket
{
    typedef HashNode<T> Node;
    public:
    HashBucket(std::size_t capacity = 10)
        :table(capacity)
        ,_size(0)
    {}

    //插入元素唯一
    bool InsertUnique(const T& date)
    {
        std::size_t bucketNo = HashFunc(date);
        Node* cur = table[bucketNo];
        while(cur)
        {
            if(cur->date == date)
                return false;
            cur = cur->next;
        }
        cur = new Node(date);
        cur->next = table[bucketNo];
        table[bucketNo] = cur;
        _size++;
        return true;
    }

    bool InsertEqual(const T& date)
    {
        std::size_t bucketNo = HashFunc(date);
        Node* cur = new Node(date);
        cur->next = table[bucketNo];
        table[bucketNo] = cur;
        _size++;
        return true;
        
    }

    bool EraseUnique(const T& date)
    {
        std::size_t bucketNo = HashFunc(date);
        Node* cur = table[bucketNo];
        Node* prev = nullptr;
        while(cur)
        {
            if(cur->date == date)
            {
                //删除
                if(cur == table[bucketNo])
                {   
                    table[bucketNo] = cur->next;
                    delete cur;
                }
                else
                {
                    prev->next = cur->next;
                    delete cur;
                }
                _size--;
                return true;
            }
            prev = cur;
            cur = cur->next;
        }
        return false;
    }

    bool EraseEqual(const T& date)
    {
        std::size_t bucketNo = HashFunc(date);
        Node* cur = table[bucketNo];
        Node* prev = nullptr;
        bool flag = false;
        while(cur)
        {
            if(cur->date == date)
            {
               if(prev == nullptr)
               {
                   table[bucketNo] = cur->next;
               }
               else
               {
                   prev->next = cur->next;
               }
               _size--;
               flag = true;
               delete cur;
               cur = nullptr;
            }
            prev = cur;
            if(prev == nullptr)
                cur = table[bucketNo];
            else
                cur = cur->next;
        }
        return flag;
    }

    Node* Find(const T& date)
    {
        std::size_t bucketNo = HashFunc(date);
        Node* cur = table[bucketNo];
        while(cur)
        {
            if(cur->date == date)
                return cur;
            cur = cur->next;
        }
        return nullptr;
    }

    std::size_t size()const
    {
        return _size;
    }

    bool empty()const
    {
        return _size == 0;
    }

    void PrintHashBucket()
    {
        for(int i = 0;i<table.capacity();i++)
        {
            cout<<"["<<i<<"]:";
            Node* cur = table[i];
            while(cur)
            {
                cout<<cur->date<<"--->";
                cur = cur->next;
            }
            cout<<"NULL"<<endl;
        }
    }
    private:
    std::size_t HashFunc(const T& date)
    {
        return date%table.capacity();
    }
    private:
        std::vector<Node*> table;
        std::size_t _size;
};




void TestHash()
{
    HashBucket<int> ht;
    int array[] = {1,4,5,6,7,9};
    for(auto e: array)
    {
        ht.InsertUnique(e);
    }
    cout<<ht.size()<<endl;

    ht.PrintHashBucket();
    cout<<endl;
    ht.InsertUnique(99);


    ht.PrintHashBucket();
}
