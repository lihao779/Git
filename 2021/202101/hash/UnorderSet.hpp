#pragma once
#include "hash.hpp"
namespace bite
{
    template<class K>
    class unordered_set
    {
        typedef K ValueType;
        struct KOFV
        {
            public:
                K& operator()(ValueType& date)
                {
                    return date;
                }
        };
        typedef HashBucket<ValueType,KOFV> HTB;

        public:
        typedef typename HTB::iterator iterator;
        public:
            unordered_set()
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
            /////////////////////
            //find
            
            iterator find(const K& key)
            {
                return _ht.Find(key);
            }

            ///////////////////////////
            //modify
            pair<iterator,bool> insert(const ValueType& val)
            {
               return  _ht.InsertUnique(val);
            }
            size_t erase(const K& key)
            {
                return _ht.EraseUnique(key);
            }
            void clear()
            {
                _ht.clear();
            }
            void swap(unordered_set<K>& s)
            {
                _ht.swap(s._ht);
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
                return _ht.Bucket(key);
            }
        private:
        HTB _ht;
        
    };

}
