#include<stdio.h>


int main()
{
    union Date
    {
        int a;
        char b;
    }date;
    date.a = 1;
    if(date.b == 1)
    {
        printf("小端存储\n");
    }
    else
        printf("大端存储\n");
    return 0;
}
