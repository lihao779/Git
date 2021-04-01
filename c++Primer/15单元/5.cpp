#include <iostream>
class B
{
    public:
        size_t size()
        {
            return n;
        }
    protected:
        int n;
    private:
        int a;
};

class D: private B
{
    public:
        using B::size;
    protected:
        using B::n;
};

int main()
{
    D d;
    d.size();
    return 0;
}
