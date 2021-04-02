#include <iostream>
#include <string>


class A
{
    public:
        void Test()const 
        {
            b = 1;
        }
    private:
        int a;
        static int b;
};
int A::b = 1;
int main()
{
    std::string str("hello");
    //const std::string::iterator it = str.begin();
    const auto it = str.begin();
    //std::string::const_iterator it = str.begin();
    //it++;
    std::cout << str << std::endl;
    return 0;
}
