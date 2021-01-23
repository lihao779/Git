#pragma once
#include "hash.hpp"
namespace bite
{
    template<class K,class V>
    class unordered_map
    {
        typedef pair<K,V> ValueType;
        struct KOFV
        {
            public:
                const K& operator()(const ValueType& date)
                {
                    return date.first;
                }
        };
        typedef HashBucket<ValueType,KOFV> HTB;

        public:
        typedef typename HTB::iterator iterator;
        public:
            unordered_map()
                :_ht()
            {}

            //////////////////////
            //iterator
            iterator begin()
            {
                return _ht.begin();
            }
            iterator end()
            {
                return _ht.end();
            }

            //////////////////////
            //capacity
            bool empty()const
            {
                return _ht.empty();
            }
            size_t size()const
            {
                return _ht.size();
            }
            /////////////////
            //acess
            V& operator[](const K& key)
            {
                return (*(_ht.InsertUnique(make_pair(key,V())).first)).second;
            }
            /////////////////////
            //find
            
            iterator find(const K& key)
            {
                return _ht.Find(make_pair(key,V()));
            }

            ///////////////////////////
            //modify
            pair<iterator,bool> insert(const ValueType& val)
            {
               return  _ht.InsertUnique(val);
            }
            size_t erase(const K& key)
            {
                return _ht.EraseUnique(make_pair(key,V()));
            }
            void clear()
            {
                _ht.clear();
            }
            void swap(unordered_map<K,V>& m)
            {
                _ht.swap(m._ht);
            }
            /////////////////////////
            //桶相关的操作
            size_t bucket_count()const
            {
                return _ht.BucketCount();
            }
            size_t bucket_size(size_t n)const
            {
                return _ht.Bucketsize(n);
            }
            size_t bucket(const K& key)
            {
                return _ht.Bucket(make_pair(key,V()));
            }
        private:
        HTB _ht;
        
    };

}


#include <iostream>
#include <string>
using namespace std;

void TestUnorderMap()
{
    bite::unordered_map<string,string> m;
    m.insert(make_pair("apple","苹果"));
    m.insert(pair<string,string>("banana","香蕉"));
    m.insert(make_pair("peach","桃子"));

    cout << m.size()<<endl;

    auto it = m.begin();
    while(it != m.end())
    {
        cout<<it->first<<"--->"<<it->second<<" ";
        it++;
    }
    cout<<endl;
    cout<<m["peach"]<<endl;
    cout<<m["orange"]<<endl;
    m.erase("orange");
    for(auto& e:m)
    {
        cout<<e.first<<"--->"<<e.second<<" ";
    }
    cout<<endl;
}



#include <unordered_map>

void Testunordered_map()
{
    unordered_map<string,string> m;
    m.insert(make_pair("apple","苹果"));
    m.insert(pair<string,string>("banana","香蕉"));
    m.insert(make_pair("peach","桃子"));

    cout << m.size()<<endl;

    auto it = m.begin();
    while(it != m.end())
    {
        cout<<it->first<<"--->"<<it->second<<" ";
        it++;
    }
    cout<<endl;
    cout<<m["peach"]<<endl;
    cout<<m["orange"]<<endl;
    m.erase("orange");
    for(auto& e:m)
    {
        cout<<e.first<<"--->"<<e.second<<" ";
    }
    cout<<endl;
}
