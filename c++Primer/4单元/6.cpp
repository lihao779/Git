#include <string>
#include <iostream>

using namespace std;

int main()
{
    string cur;
    string prev;
    while(cin >> cur)
    {
        if(!prev.empty() && !prev.compare(cur))
            break;
        prev = cur;
    }
    return 0;
}
