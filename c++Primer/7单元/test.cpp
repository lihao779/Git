#include <iostream>
#if 0
class A
{
    public:
        A(int a = int())
            :a_(a)
        {}
        int Geta()
        {
            return a_;
        }
    private:
        int a_;
};

int main()
{
    A a(2);
    std::cout << a.Geta() << std::endl;
    A b;
    std::cout << b.Geta() << std::endl;
    b = a;
    std::cout << a.Geta() << std::endl;
    std::cout << b.Geta() << std::endl;
    return 0;
}
#endif
#if 0
class A
{
    public:
        A()
            :a(0)
        {}
        ~A()
        {}

        void set(int num)
        {
            a = num;
            std::cout << a << std::endl;
            clear();
            std::cout << a << std::endl;
        }
        void clear()
        {
            a = 0;
        }
    private:
        int a;
};
int main()
{
    A a;
    a.set(1);
    return 0;
}
#endif

#include <string>
using namespace std;
typedef string Type;
Type initVal();

class Exercise
{
    public:
        typedef int Type;
        Type setVal(Type);
        Type initVal()
        {
            cout << "11" <<endl;
            return 1;
        }
    private:
        int val;
};
Exercise::Type Exercise::setVal(Type pram)
{
    val = pram + initVal();
    return val;
}

int main()
{
    Exercise a;
    a.setVal(1);
    return 0;
}
