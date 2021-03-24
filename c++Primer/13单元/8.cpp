#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


class HasPtr
{
    friend void swap(HasPtr& p1, HasPtr& p2);
    public:
        HasPtr(const std::string& s = std::string()) : ps(new std::string(s)), i(0){}
        HasPtr(const HasPtr& s) : ps(new std::string(*s.ps)), i(s.i){}
        bool operator<(const HasPtr& s)
        {
            return *ps < *s.ps;
        }

        HasPtr& operator=(const HasPtr& s)
        {
            if(this != &s)
            {
                std::string* temp = new std::string(*s.ps);
                delete ps;
                ps = temp;
                i = s.i;
            }
            return *this;
        }

        ~HasPtr() { delete ps; }
    private:
        std::string* ps;
        int i;
};

void swap(HasPtr& p1, HasPtr& p2)
{
    std::swap(p1.i, p2.i);
    std::swap(p1.ps, p2.ps);
    std::cout << "swap()" << std::endl;
}

int main()
{
    std::vector<HasPtr> vec;
    for(int i = 0; i < 100; i++)
        vec.push_back(HasPtr("1"));
    sort(vec.begin(), vec.end());
    return 0;
}
