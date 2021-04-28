#include <stdio.h>
#include <vector>
using namespace std;
int addfrom2_toN(int n)
{
    if(n == 1)
        return 1;
    return n + addfrom2_toN(n - 1);
}
int addfrom1_toN(size_t n)
{
    int result = 0;
    for(size_t i = 1; i <= n; i++)
        result += i;
    return result;
}


int main()
{
    int i1 = 5000000;
    size_t i2 = 5000000;
    printf("%d\n", addfrom2_toN(i1));
    printf("%d\n", addfrom1_toN(i2));
    return 0;
}
