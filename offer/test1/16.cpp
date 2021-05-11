#include <vector>
#include <string.h>
#include <iostream>
using namespace std;


void _Print(char* ptr, int i, vector<char> vec)
{
    if(ptr == NULL || i < 0 || (*ptr == '\0' && i != 0))
        return;
    if(i  == 0)
    {
        for(auto& e: vec)
            cout << e;
        cout << " ";
        return;
    }
    vec.push_back(*ptr);
    _Print(ptr + 1, i - 1, vec);
    vec.pop_back();
    _Print(ptr + 1, i, vec);
}

void Print(char* ptr)
{
    if(ptr == NULL)
        return;
    int sz = strlen(ptr);
    for(int i = 1; i <= sz; i++)
    {
        vector<char> vec;
        _Print(ptr, i, vec);
    }
}

int main()
{
    char ptr[] = "123";
    Print(ptr);
    return 0;
}
