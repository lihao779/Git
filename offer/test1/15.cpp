#include <iostream>
using namespace std;
void swap(char* left, char* right)
{
    char temp = *left;
    *left = *right;
    *right = temp;
}
void _Print(char* ptr, char* begin)
{
    if(*begin == '\0')
        cout << ptr << " ";
    for(char* i = begin; *i != '\0'; i++)
    {
        swap(i, begin);
        _Print(ptr, begin+1);
        swap(i, begin);
    }
}


void Print(char* ptr)
{
    if(ptr == NULL)
        return;
    _Print(ptr, ptr);
}

int main()
{
    char ptr[] = "123";
    Print(ptr);
    return 0;
}
