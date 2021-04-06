
class A
{
    public:
        A()
        {
            test();
        }
    virtual void test() = 0;
};

class B: public A
{

    virtual void test()
    {

    }
};


int main()
{
    B b;
    return 0;
}
