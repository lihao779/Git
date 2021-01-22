#include "hash.hpp"
#include <iostream>
#include <cstdio>
using namespace std;


void Test1()
{
    for(int i = 1;i<=9;i++)
    {
        for(int j = 1;j<=i;j++)
        {
            printf("%2d*%-2d=%-4d",j,i,j*i);
        }
        cout<<endl;
    }
}

int main()
{
    TestHash1();
    TestHash2();

    return 0;
}
