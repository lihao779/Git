#include <iostream>
template<typename T>
void print(std::ostream& os, const T& con)
{
    for(typename T::size_type i = 0; i < con.size(); i++)
    {
        os << con[i] << " ";
    }
}

template<typename T>
void Print(std::ostream& os, const T& con)
{
    auto it = con.begin();
    while(it != con.end())
        os << *it++ << " ";
}


#include <string>

int main()
{
    std::string s = "hello";
    print(std::cout, s);
    Print(std::cout, s);
    return 0;
}
