#include <stdio.h>


int countofone(int i)
{
    int count = 0;
    char flag = 1;
    while(flag)
    {
        if(i & flag)
            count++;
        flag <<= 1;
    }
    return count;
}

int main()
{
    int i;
    scanf("%d", &i);
    printf("count = %d\n", countofone(i));
    return 0;
}
