#include <iostream>
#include <string>

using namespace std;

class StrPtr
{
    public:
        StrPtr(const string& s = string())
            :ps(new string(s))
             ,i(0)
             ,user(new size_t(1))
        {}

        StrPtr(const StrPtr& s)
            :ps(s.ps)
             ,i(s.i)
             ,user(s.user)
        {
            ++*user;
        }

        StrPtr& operator=(const StrPtr& s)
        {
            if(&s != this)
            {
                if(--*user == 0)
                {
                    delete user;
                    delete ps;
                    user = nullptr;
                    ps = nullptr;
                }
                ps = s.ps;
                user = s.user;
                i = s.i;
                ++*user;
            }
            return *this;
        }
        ~StrPtr()
        {
            if(ps && --*user == 0)
            {
                delete ps;
                delete user;
                ps = nullptr;
                user = nullptr;
            }
        }
    private:
        string* ps;
        int i;
        size_t* user;
};

int main()
{
    return 0;
}
