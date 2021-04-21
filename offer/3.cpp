#include <stdio.h>

#if 0
bool IsHavenum(int array[3][3], int row, int col, int num)
{
    int temprow = 0;
    int tempcol = col - 1;
    int temp = -1;

    while(temprow <= row - 1 && tempcol >= 0)
    {
        temp = array[temprow][tempcol];
        if(temp == num)
            return true;
        else if(temp > num)
            tempcol--;
        else
            temprow++;
    }
    return false;

    
}
#endif

bool IsHavenum(int array[][3], int row, int col, int num)
{
    int temprow = row - 1;
    int tempcol = 0;
    while(array != NULL && temprow >= 0 && tempcol <= col - 1)
    {
        int temp = array[temprow][tempcol];
        if(temp == num)
            return true;
        else if(temp > num)
            temprow--;
        else 
            tempcol++;
    }
    return false;
}
int main()
{
    int array[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
    int row , col;
    row = col = 3;
    if(IsHavenum(array, row, col, 7))
    {
       printf("have 7\n"); 
    }
    else
        printf("not have 7\n");
    return 0;
}
