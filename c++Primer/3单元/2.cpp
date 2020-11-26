#include <stdio.h>
#include <iterator>
using namespace std;
int main()
{
    int array[3][2] = {{1,2},{3,4},{5,6}};
    for(auto p = array;p != array+3;p++)
    {
        for(auto q = *p;q != *p+2;q++)
        {
            printf("%d ",*q);
        }
        printf("\n");
    }
    for(auto p = begin(array);p!=end(array);p++)
    {
        for(auto q = begin(*p);q!=end(*p);q++)
        {
            printf("%d ",*q);
        }
        printf("\n");
    }
    return 0;
}
