#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
using namespace std;


class HasPtr
{
    public:
        HasPtr(const string& s = string(), int i = 0)
            :s_(new string(s))
             ,i_(i)
        {}

        HasPtr(const HasPtr& h)
            :s_(new string(*h.s_))
             ,i_(h.i_)
        {}

        HasPtr& operator=(const HasPtr& h)
        {
            if(&h != this)
            {
                string* temp = new string(*h.s_);
                delete s_;
                s_ = temp;
                i_ = h.i_;
            }
            return *this;
        }
        
        void swap(HasPtr& h)
        {
            std::swap(h.i_,i_);
            std::swap(h.s_,s_);
            cout << "swap(HasPtr&)" << endl;
        }
        bool operator<(const HasPtr& h)const
        {
            return i_ < h.i_;
        }
        
        ~HasPtr()
        {
            if(s_)
            {
                delete s_;
                s_ = nullptr;
            }
        }
    private:
        string* s_;
        int i_;
};


int main()
{
    vector<HasPtr> vec;
    for(int i = 100; i >= 0; i--)
        vec.push_back(HasPtr("1", i));
    sort(vec.begin(), vec.end());
    return 0;
}
