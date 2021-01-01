#include<vector>
#include<iostream>
#include<stdio.h>
#include<string.h>

using namespace std;

void TestVector1(int row,int col)
{
    int** Row = new int*[row];
    for(int i  = 0;i<row;++i)
    {
        Row[i] = new int[col];
        memset(Row[i],0,sizeof(int)*col);
    }
    
    for(int i = 0;i<row;++i)
    {
        for(int j = 0;j<col;++j)
        {
            cout<<Row[i][j]<<" ";
        }
        cout<<endl;
    }

    for(int i = 0;i<row;++i)
    {
        delete[] Row[i];
    }
    delete[] Row;
}

/*
 * 1
 * 1 1
 * 1 2 1
 * 1 3 3 1
 * 1 4 6 4 1
 */
void TestVector2(int row)
{
    vector<vector<int>> vv;
    //开辟保存每一行元素
    vv.resize(row);
    //开辟每行空间
    for(int i = 0;i<row;++i)
    {
        vv[i].resize(i+1,1);
    }

    for(int i = 2;i<row;++i)
    {
        for(int j = 1;j<i;++j)
        {
            vv[i][j] = vv[i-1][j]+vv[i-1][j-1];
        }
    }
    for(int i = 0;i<row;++i)
    {
        for(int j = 0;j<i+1;j++)
        {
            printf("%3d ",vv[i][j]);
        }
        cout<<endl;
    }
}

int main()
{
    // TestVector1(3,10);
    TestVector2(10);
    return 0;
}
