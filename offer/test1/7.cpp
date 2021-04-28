#if 0
long long Fib(unsigned int n)
{
    if(n <= 1)
        return n;
    return Fib(n - 1) + Fib(n - 2);
}
#endif
long long Fib(unsigned int n)
{
    int fib[2] = {0 , 1};
    if(n < 2)
        return fib[n];
    
    int first = 0;
    int second = 1;
    int result;
    for(int i = 2; i <= n ;i++)
    {
        result = first + second;
        first = second;
        second = result;
    }
    return result;
}
#include <stdio.h>

int main()
{
    unsigned int i;
    scanf("%ud", &i);
    printf("%lld\n",Fib(i));
    return 0;
}
