#pragma once
#include "common.h"
#include <vector>
#include <iostream>
using namespace std;



template<class T>
class DToIntDef
{
    public:
        const T& operator()(const T& date)
        {
            return date;
        }
};
#if 0
class DToIntStr
{
    public:
        size_t operator()(const string& str)
        {
            size_t ret = 0;
            for(size_t i = 0;i<str.size();i++)
            {
                ret +=str[i];
            }
            return ret;
        }
};

#endif
class DToIntStr
{
    public:
        size_t operator()(const string& str)
        {
            return BKDRhash(str.c_str());
        }
        size_t BKDRhash(const char* str)
        {
            size_t seed = 131;
            size_t hash = 0;
            while(*str)
            {
                hash = hash * seed + (*str++);
            }
            return (hash & 0x7FFFFFFF);
        }

};

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

template<class T,class DToInt = DToIntDef<T>>
class  HashBucket
{
    typedef HashNode<T> Node;
    public:
    HashBucket(std::size_t capacity = 10)
        :table(GetNextPrime(capacity))
        ,_size(0)
    {}
    
    ~HashBucket()
    {
        clear();
    }

    void clear()
    {
        for(int i = 0;i<table.capacity();i++)
        {
            Node* cur = table[i];
            while(cur)
            {
                table[i] = cur->next;
                delete cur;
                cur = table[i];
            }
        }
    }


    //插入元素唯一
    bool InsertUnique(const T& date)
    {
        _Checkcapacity();
        std::size_t bucketNo = HashFunc(date,table.capacity());
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
        std::size_t bucketNo = HashFunc(date,table.capacity());
        Node* cur = new Node(date);
        cur->next = table[bucketNo];
        table[bucketNo] = cur;
        _size++;
        return true;
        
    }

    bool EraseUnique(const T& date)
    {
        std::size_t bucketNo = HashFunc(date,table.capacity());
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
        std::size_t bucketNo = HashFunc(date,table.capacity());
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
        std::size_t bucketNo = HashFunc(date,table.capacity());
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
        cout<<endl;
    }
    void swap(HashBucket<T,DToInt>& ht)
    {
        // std::swap(table,ht.table);
        table.swap(ht.table);
        std::swap(_size,ht._size);
    }
    private:
    /*
    void _Checkcapacity()
    {
        if(_size == table.capacity())
        {
            HashBucket<T,DToInt> newht(2*table.capacity());
            for(int i = 0;i<table.capacity();i++)
            {
                Node* cur = table[i];
                while(cur)
                {
                    newht.InsertEqual(cur->date);
                    cur = cur->next;
                }
            }
            swap(newht);
        }
    }
    */
    void _Checkcapacity()
    {
        if(_size == table.capacity())
        {
            std::vector<Node*> newtable(GetNextPrime(table.capacity()));
            for(int i = 0;i<table.capacity();i++)
            {
                Node* cur = table[i];
                while(cur)
                {
                    table[i] = cur->next;
                    size_t BucketNo = HashFunc(cur->date,newtable.capacity());
                    cur->next = newtable[BucketNo];
                    newtable[BucketNo] = cur;
                    cur = cur->next;
                }
            }
            table.swap(newtable);
        }
    }
    std::size_t HashFunc(const T& date,size_t capacity)
    {
        // DToInt dtoi;
        // return dtoi(date)%capacity;
        return DToInt()(date)%capacity;
    }
    private:
        std::vector<Node*> table;
        std::size_t _size;
};




void TestHash1()
{
    HashBucket<int,DToIntDef<int>> ht;
    int array[] = {1,4,5,6,7,9,3,2,18,0};
    for(auto e: array)
    {
        ht.InsertUnique(e);
    }
    cout<<ht.size()<<endl;

    ht.PrintHashBucket();
    ht.InsertUnique(19);


    ht.PrintHashBucket();
}
#include <string>
void TestHash2()
{
    HashBucket<string,DToIntStr> ht;
    ht.InsertUnique("apple");
    ht.InsertUnique("banana");
    ht.InsertUnique("organe");
    ht.InsertUnique("appel");
    ht.PrintHashBucket();
}
