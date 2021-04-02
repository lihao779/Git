
#include <iostream>
class String
{
    public:
        const char& operator[](size_t index)const
        {
            return ptr[index];
        }
        char& operator[](size_t index)
        {
            return const_cast<char&>
                (static_cast<const String>(*this)[index]);
        }
    private:
        char* ptr;
};


class A
{
    public:
        A() { std::cout << "A()" << std::endl; }
        A& operator=(const A& a)
        {
            std::cout << "A& operator=(const A&)" << std::endl;
            return *this;
        }
};

class B
{
    public:
        B()
        {
           a = A();
        }
    private:
        A a;
};
 int main()
{
    B b;
    return 0;
}
