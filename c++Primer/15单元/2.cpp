#include <iostream>
#include <string>
class Base
{
    public:
    virtual void Test(int a = 1)
    {
        std::cout << "Base::Test(int a = 1) :a = " << a << std::endl;
    }
};
class Derived: public Base
{
    public:
    virtual void Test(int a = 2) override
    {
        std::cout << "Derived::Test(int a = 2) :a = " << a << std::endl;
    }
};
class B
{
    public:
        B(std::string name): name_(name) {}
        virtual void print(std::ostream& os) { os << name_; }
    private:
        std::string name_;
};
class D : public B
{
    public:
        D(std::string name, int i):B(name), i_(i) {}
        virtual void print(std::ostream& os) override { B::print(os); os << " " << i_ ; }
    private:
        int i_;
};

int main()
{
    D d("C", 1);
    B* ptr = &d;
    ptr->print(std::cout);
    std::cout << std::endl;
    B& ra= d;
    ra.print(std::cout);
    std::cout << std::endl;
    return 0;
}
