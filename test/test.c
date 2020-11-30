#include <stdio.h>

struct A
{
    int a;
};
int main()
{
    A a;
    printf("%p,%p\n",a,&a);
    return 0;
}
