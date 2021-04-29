
#include <stdio.h>

void print(int n)
{
    int num = 1;
    for(int i = 0; i < n; i++)
    {
        num *= 10;
    }
    for(int i = 0 ; i < num; i++)
    {
        printf("%d ",i);
    }
    printf("\n");
}

int main()
{
    int i;
    while(scanf("%d", &i))
        print(i);
    return 0;
}
