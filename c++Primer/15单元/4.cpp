
#include <iostream>

class B
{
    friend void Test(B&);
    public:
        int pub_ele;
    protected:
        int pro_ele;
    private:
        int pri_ele;
};
class D1: public B
{
    void Test()
    {
        pub_ele = 1;
        pro_ele = 1;
    }
};
class D2: protected B
{
    void Test()
    {
        pub_ele = 1;
        pro_ele = 1;
    }
};
class D3: private B
{
    void Test()
    {
        pub_ele = 1;
        pro_ele = 1;
    }
};
class H1: public D1
{
    void Test()
    {
        pub_ele = 1;
        pro_ele = 1;
    }
};
class H2: public D2
{
    void Test()
    {
        pub_ele = 1;
        pro_ele = 1;
    }
};
class H3: public D3
{
};

void Test(B& d)
{
    d.pub_ele = 1;
    d.pro_ele = 1;
    d.pri_ele = 1;
}

int main()
{
    H1 h;
    D2 h2;
    B& ra = h;
    B& raa = h2;
    return 0;
}
