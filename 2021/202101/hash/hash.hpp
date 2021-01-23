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
///////////////////////////////
//iterator
template<class T,class KOFV,class DToInt = DToIntStr>
class  HashBucket;

template<class T,class KOFV,class DToInt>
class HashIterator
{
    typedef HashNode<T> Node;
    typedef HashIterator<T,KOFV,DToInt> Self;
    public:
        HashIterator(Node* x = nullptr,HashBucket<T,KOFV,DToInt>* y = nullptr)
            :pNode(x)
             ,ht(y)
        {}

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
            Increatment();
            return *this;
        }
        Self operator++(int)
        {
            Self temp(*this);
            Increatment();
            return temp;
        }
        bool operator==(const Self& s)
        {
            return pNode == s.pNode && ht == s.ht;
        }
        bool operator!=(const Self& s)
        {
            return pNode != s.pNode || ht != s.ht;
        }
    private:
        void Increatment()
        {
            if(pNode->next)
                pNode = pNode->next;
            else
            {
                size_t BucketNo = ht->HashFunc(pNode->date,ht->BucketCount());
                for(int i = BucketNo+1;i<ht->table.capacity();i++)
                {
                    if(ht->table[i])
                    {
                        pNode = ht->table[i];
                        return;
                    }
                }
                pNode = nullptr;

            }
        }
    private:
        Node* pNode;
        HashBucket<T,KOFV,DToInt>* ht;
};






template<class T,class KOFV,class DToInt>
class  HashBucket
{
    friend class HashIterator<T,KOFV,DToInt>;
    typedef HashNode<T> Node;
    public:
    typedef HashIterator<T,KOFV,DToInt> iterator;
    public:
    HashBucket(std::size_t capacity = 10)
        :table(GetNextPrime(capacity))
        ,_size(0)
    {}
    
    ~HashBucket()
    {
        clear();
    }

    iterator begin()
    {
        for(int i = 0;i<BucketCount();i++)
        {
            if(table[i])
                return iterator(table[i],this);
        }
        return end();
    }

    iterator end()
    {
        return iterator(nullptr,this);
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
    pair<iterator,bool> InsertUnique(const T& date)
    {
        _Checkcapacity();
        std::size_t bucketNo = HashFunc(date,table.capacity());
        Node* cur = table[bucketNo];
        while(cur)
        {
            if(KOFV()(cur->date) == KOFV()(date))
                return make_pair(iterator(cur,this),false);
            cur = cur->next;
        }
        cur = new Node(date);
        cur->next = table[bucketNo];
        table[bucketNo] = cur;
        _size++;
        return make_pair(iterator(cur,this),true);
    }

    pair<iterator,bool> InsertEqual(const T& date)
    {
        std::size_t bucketNo = HashFunc(date,table.capacity());
        Node* cur = new Node(date);
        cur->next = table[bucketNo];
        table[bucketNo] = cur;
        _size++;
        return make_pair(iterator(cur,this),true);
        
    }

    size_t EraseUnique(const T& date)
    {
        std::size_t bucketNo = HashFunc(date,table.capacity());
        Node* cur = table[bucketNo];
        Node* prev = nullptr;
        while(cur)
        {
            if(KOFV()(cur->date) == KOFV()(date))
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
                return 1;
            }
            prev = cur;
            cur = cur->next;
        }
        return 0;
    }

    size_t EraseEqual(const T& date)
    {
        std::size_t bucketNo = HashFunc(date,table.capacity());
        Node* cur = table[bucketNo];
        Node* prev = nullptr;
        size_t flag = 0;
        while(cur)
        {
            if(KOFV()(cur->date) == KOFV()(date))
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
               flag++;
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

    iterator Find(const T& date)
    {
        std::size_t bucketNo = HashFunc(date,table.capacity());
        Node* cur = table[bucketNo];
        while(cur)
        {
            if(KOFV()(cur->date) == KOFV()(date))
                return iterator(cur,this);
            cur = cur->next;
        }
        return iterator(nullptr,this);
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
    void swap(HashBucket<T,KOFV,DToInt>& ht)
    {
        // std::swap(table,ht.table);
        table.swap(ht.table);
        std::swap(_size,ht._size);
    }

    /////////////////////////////////////////
    //桶
    //返回桶的个数
    size_t BucketCount()
    {
        return table.capacity();
    }
    // 返会桶中有几个节点
    size_t Bucketsize(size_t bucketNo)
    {
        if(bucketNo > BucketCount())
            return 0;
        else
        {
            Node* cur = table[bucketNo];
            size_t count = 0;
            while(cur)
            {
                count++;
                cur = cur->next;
            }
            return count;
        }
    }
    //返回date所在桶号
    size_t Bucket(const T& date)
    {
        return HashFunc(date,BucketCount());
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
        return DToInt()(KOFV()(date))%capacity;
    }
    private:
        std::vector<Node*> table;
        std::size_t _size;
};




template<class T>
class K_Int
{
    public:
        const T& operator()(const T& date)
        {
            return date;
        }
};

void TestHash1()
{
    HashBucket<int,K_Int<int>,DToIntDef<int>> ht;
    int array[] = {1,4,5,6,7,9,3,2,18,0};
    for(auto e: array)
    {
        ht.InsertUnique(e);
    }
    cout<<ht.size()<<endl;

    ht.PrintHashBucket();
    ht.InsertUnique(19);


    ht.PrintHashBucket();
    auto it = ht.begin();
    while(it != ht.end())
    {
        cout<<*it<<" ";
        it++;
    }
    cout<<endl;
}
#include <string>
void TestHash2()
{
    HashBucket<string,K_Int<string>,DToIntStr> ht;
    ht.InsertUnique("apple");
    ht.InsertUnique("banana");
    ht.InsertUnique("organe");
    ht.InsertUnique("appel");
    ht.PrintHashBucket();
}
