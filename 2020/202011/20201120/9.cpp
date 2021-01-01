#include<stdio.h>
#include<vector>
#include<iostream>
using namespace std;
int main()
{
    /*
    int a = 1;
    int b = 2 ;
    a+=b-a;//先执行b-a在执行+=
    printf("%d\n",a);
    */
    int array[10] = {1,2,3,4,5,6,7,8,9,10};
    for(int i = 0;i<10;i++)
    {
        cout<<"array["<<i<<"]"<<" = "<<array[i]<<" ";
    }
    cout<<endl;
    int* p = array;
    for(int j = 0;j<10;j++)
    {
        *p = 0;
        cout<<"array["<<j<<"]"<<" = "<<array[j]<<" ";
        p++;
    }
    cout<<endl;
    int array2[10] = {0};
    int i = 0;
    for( i = 0;i<10;i++)
    {
        if(array[i] != array2[i])
            break;
    }
    if(i == 10)
    {
        cout<<"array = array2"<<endl;
    }
    vector<int> vec1(10,1);
    vector<int> vec2(10,1);
    if(vec1 == vec2)
    {
        cout<<"vec1 = vec2"<<endl;
    }
    return 0;
}
