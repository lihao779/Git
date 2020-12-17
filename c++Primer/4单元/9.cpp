#include <iostream>
using namespace std;


/*
int fact(int val)
{
    int ret = 1;
    while(val > 1)
    {
        ret *= val--;
    }
    return ret;
}
*/

int fact(int val)
{
    int ret = 1;
    while(val > 1)
    {
        ret *= val--;
    }
    return ret;
}
int staticfun()
{
    static int a = 0;
    return a++;
}



int main()
{
    for(int i = 0;i<10;i++)
        cout<<staticfun()<<endl;
    return 0;
}
