#include <iostream>
#include <memory>

class A
{
    public:
    A()
    {
        std::cout << "A()" << std::endl;
    }
    virtual ~A()
    {
        std::cout << "~A()" << std::endl;
    }
};
class B: public A
{
    public:
        B()
           :A()
        {
            std::cout << "B()" << std::endl;
        }
        ~B()
        {
            std::cout << "~B()" << std::endl;
        }
};

#include <vector>
int main()
{
    /*
    std::vector<std::shared_ptr<A>> v;
    v.push_back(std::shared_ptr<A>(new A()));
    v.push_back(std::shared_ptr<B>(new B()));

    */
    std::vector<A*> v1;
    v1.push_back(new A);
    v1.push_back(new B);
    delete v1[0];
    delete v1[1];
    
    return 0;
}
//std::vector<std::shared_ptr<A>> v;
//v.push_back(std::make_shared<A>());
//v.push_back(std::make_shared<B>());
