#include "RBTree.hpp"


template<class K,class V>
class map
{
    typedef pair<K,V> ValueType;
    class KOFV
    {
        public:
            const K& operator()(const ValueType& date)const 
            {
                return date.first;
            }
    };
    typedef RBTree<ValueType,KOFV> RBtree;
    typedef typename RBtree::iterator iterator;
    public:
    map()
        :_t()
    {}

    //////////////////
    iterator begin()
    {
        return _t.begin();
    }
    iterator end()
    {
        return _t.end();
    }
    bool empty()const
    {
        return _t.empty();
    }
    size_t size()
    {
        return _t.size();
    }
    V& operator[](const K& key)
    {
        return (*((this->insert(make_pair(key,V()))).first)).second;
    }
    pair<iterator,bool> insert(const ValueType& value)
    {
        return _t.Insert(value);
    }
    void swap(map<K,V> m)
    {
        _t.swap(m._t);
    }
    void clear()
    {
        _t.clear();
    }

    iterator find(const K& key)
    {
        return _t.find(make_pair(key,V()));
    }

    private:
    RBtree _t;
};



void Testmap()
{
    map<string,string> m;
    m.insert(make_pair("apple","苹果"));
    m.insert(make_pair("banana","香蕉"));
    m.insert(make_pair("orange","橙子"));

    cout<<m["apple"]<<endl;
    cout<<m.size()<<endl;
    auto it = m.find("apple");
    if(it != m.end())
    {
        cout<<it->second<<endl;
    }
    it = m.begin();
    while(it != m.end())
    {
        cout<<"<"<<it->first<<"-"<<it->second<<">"<<endl;
        ++it;
    }
}
