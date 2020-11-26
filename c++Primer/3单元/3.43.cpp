#include <stdio.h>

int main()
{
    int ia[2][3] = {{1,2,3},{4,5,6}};
    for(auto& row:ia)
    {
        for(auto col:row)
        {
            printf("%d ",col);
        }
        printf("\n");
    }
    for(int(*p)[3] = ia;p!=ia+2;p++)
    {
        for(int*q = *p;q!=*p+3;q++)
        {
            printf("%d ",*q);
        }
        printf("\n");
    }
    for(int row = 0;row<2;row++)
    {
        for(int col = 0;col<3;col++)
        {
            printf("%d ",ia[row][col]);
        }
        printf("\n");
    }
    return 0;
}
