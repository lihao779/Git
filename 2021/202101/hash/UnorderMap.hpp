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
            const K& operator()(const ValueType& date)
            {
                return date.first;
            }
        };
        typedef HashBucket<ValueType,KOFV>;
    private:
        
    };

}
