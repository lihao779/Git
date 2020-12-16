#include <iostream>
using namespace std;

int fact(int val)
{
    int ret = 1;
    while(val > 1)
    {
        ret *= val--;
    }
    return ret;
}


int main()
{
    cout << "3! is"<<fact(3)<<endl;
    return 0;
}
