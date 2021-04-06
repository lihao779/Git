
typedef void(*PF)(int&, int&&);
#include<utility>
template<typename T1, typename T2>
void Func(PF f, T1&& t1, T2&& t2)
{
    f(std::forward<T1>(t1), std::forward<T2>(t2));
}
