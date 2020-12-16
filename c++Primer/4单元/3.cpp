#include <stdio.h>
#include <iostream>
#include <typeinfo>
#include <string>

using namespace std;
int main()
{
    int a = 1;
    switch(a)
    {
        case 1:
            int b ;
            printf("%d\n",b);
            break;
        case 2:
            b = 1;
            printf("%d\n",b);
            break;
        case 3:
            printf("%d\n",b);
            break;
    }
    return 0;
}
