#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class StrBlob
{
    public:
    typedef vector<string>::size_type size_type;
    StrBlob()
        :data(make_shared<vector<string>>())
    {}
    StrBlob(initializer_list<string> li)
        :data(make_shared<vector<string>>(li))
    {}
    
    size_type size()
    {
        return data->size();
    }
    bool empty()
    {
        return data->empty();
    }
    void push_back(const string& s)
    {
        data->push_back(s);
    }
    void pop_back()
    {
        check(0, "元素为空");
        data->pop_back();
    }
    string& front()
    {
        check(0, "元素为空");
        return data->front();
    }
    const string& front()const
    {
        check(0, "元素为空");
        return data->front();
    }
    string& back()
    {
        check(0, "元素为空");
        return data->back();
    }
    const string& back()const
    {
        check(0, "元素为空");
        return data->back();
    }

    private:
    void check(size_type i, const string& s)const
    {
        if(i >= data->size())
            throw out_of_range(s);
    }
    private:
        shared_ptr<vector<string>> data;
        
};
int main()
{
    StrBlob b1;
    {
        StrBlob b2 = {"a", "an", "the"};
        b1 = b2;
        cout << "b1.size:" << b1.size() << " b2.size:" << b2.size() << endl;
        b2.push_back("aaa");
        cout << "b1.size:" << b1.size() << " b2.size:" << b2.size() << endl;
    }
    cout << "b1.size:" << b1.size() << endl;
    cout << "b1.front:" << b1.front() << " b1.back:" << b1.back() << endl;
    StrBlob b3 = b1;
    cout << "b3.front:" << b3.front() << " b3.back:" << b3.back() << endl;

    return 0;
}
