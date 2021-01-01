#include <iostream>
using namespace std;

#define SQL(A) A*A

int main()
{
    cout<<SQL(3+2)/SQL(3+2)<<endl;
    return 0;
}
