#include <stdio.h>

int main()
{
    int array[2][3] = {0};
    int cnt = 0;
    for(auto& e1:array)
    {
        for(auto& e2:e1)
        {
            e2 = cnt;
            cnt++;
        }
    }
    for(const auto& row:array)
    {
        for(auto col:row)
        {
            printf("%d ",col);
        }
        printf("\n");
    }
    for(int i = 0;i<2;i++)
    {
        for(int j = 0;j<3;j++)
        {
            printf("%d ",array[i][j]);
        }
        printf("\n");
    }

    return 0;
}
