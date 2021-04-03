#include <cstddef>
#include <iostream>
template<size_t N, class T>
void print(std::ostream& os, T (&arr)[N])
{
//    for(auto& e: array)
//        os << e << " ";
    for(size_t i = 0; i < N; i++)
        os << arr[i] << " ";
}

template<class T, size_t N>
const T* begin(const T (&arr)[N])
{
    return &arr[0];
}
template<class T, size_t N>
const T* end(const T (&arr)[N])
{
    return &arr[0] + N;
}

template<size_t N, class T>
constexpr int arrsize(const T (&arr)[N])
{
    return N;
}

int main()
{
    //int arr[]= {1, 2, 3, 4, 5, 6};
    //print(std::cout, arr);
    return 0;
}
