#include <algorithm>
#include<string>
#include<iostream> 
#include <vector>

using namespace std;
class HasPtr
{
    friend void swap(HasPtr & lhs, HasPtr & rhs); 
    public:
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) {  }
    HasPtr(const HasPtr & hp): ps(new std::string(*hp.ps)), i(hp.i) {  }
    bool operator<(const HasPtr & rhs);
    std::ostream & print(std::ostream & os) const 
    {
        os << *ps << " " << i;
        return os;

    }

    HasPtr & operator=(const HasPtr & rhs);

    ~HasPtr() { delete ps;  }

    private:
    std::string *ps;
    int i;

};

HasPtr & HasPtr::operator=(const HasPtr & rhs)
{
    std::string * newp = new std::string(*rhs.ps);
    delete ps;
    ps = newp;
    i = rhs.i;
    return *this;

}

bool HasPtr::operator<(const HasPtr & rhs)
{
    return *ps < *(rhs.ps);

}

void swap(HasPtr & lhs, HasPtr & rhs)
{
    using std::swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);
    std::cout << "void swap(HasPtr & lhs, HasPtr & rhs)" << std::endl;

}

int main()
{
    vector<HasPtr> vec;
    for(int i = 0; i < 100; i++)
        vec.push_back(HasPtr("s"));
    sort(vec.begin(), vec.end());
    return 0;
}
