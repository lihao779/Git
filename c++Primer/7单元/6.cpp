class Y;
class X;

class X
{
    Y* ptr_;
};


class Y
{
    X x_;
};


void f1();
class XX
{
    friend void f1()
    {}
    public:
    XX()
    {
        f1();
    }
};
void y()
{
    f1();
}
