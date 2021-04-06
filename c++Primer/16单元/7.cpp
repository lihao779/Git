class DeleteDebug
{
    public:
        template<typename T>
        void operator()(T* p)const 
        {
            delete p;
        }
};

#include <iostream>
template<typename T>
void Test(const T& t1, const T& t2)
{
    std::cout << t1[0] << " " << t2[0] << std::endl;
}

#include <type_traits>
template<typename It>
auto func(It b, It e)-> typename std::remove_reference<decltype(*b)>::type
{
    return *b;
}
template<typename T>
void Test1(T&& t)
{
    t = 1;
}

int main()
{
    typedef int&& T; 
    int arr1[10] = {1};
    int arr2[10] = {2};
    Test(arr1, arr2);
    Test("hello", "world");
    std::cout << std::max<int>(1, 4.0) << std::endl;
    std::cout << std::max<double>(1, 4.0) << std::endl;
    decltype(1) a = 1;
    std::cout << a << std::endl;
    T&& ra  = 1 ;
    int a1 = 0;
    Test1(a1);
    Test1(1);
    std::cout << a1 << std::endl;
    return 0;
}
