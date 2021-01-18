#include "RBTree.hpp"


template<class K>
class set
{
    typedef K ValueType;
    class KOFV
    {
    public:
        const K& operator()(const ValueType& v)const
        {
            return v;
        }

    };
    typedef RBTree<ValueType,KOFV> RBtree;
    typedef typename RBtree::iterator iterator;
    public:
    set()
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
    pair<iterator,bool> insert(const ValueType& value)
    {
        return _t.Insert(value);
    }
    void swap(set<K> s)
    {
        _t.swap(s._t);
    }
    void clear()
    {
        _t.clear();
    }

    iterator find(const K& key)
    {
        return _t.find(key);
    }

    private:
    RBtree _t;
};


void SetTest()
{
    set<string> s;
    s.insert("apple");
    s.insert("banana");
    s.insert("oragne");

    cout<<s.size()<<endl;
    auto it = s.find("apple");
    if(it != s.end())
    {
        cout<<*it<<endl;
    }
    it = s.begin();
    while(it != s.end())
    {
        cout<<*it<<" ";
        it++;
    }
    cout<<endl;
}
