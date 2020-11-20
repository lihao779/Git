#include<cstring>
#include<iostream>
#include<vector>

using namespace std;

int main()
{
    int array1[10] = {1,2,3,4,5,6,7,8,9,10};
    int array2[10] = {1,2,3,4,5,6,7,8,9,10};
    int flag = 0;
    if(sizeof(array1)==sizeof(array2))
    {
        for(size_t i = 0;i<sizeof(array1)/sizeof(array1[0]);i++)
        {
            if(array1[i] == array2[i])
            {
                flag++;
            }
        }
    }
    if(flag == sizeof(array1)/sizeof(array1[0]))
        cout<<"array1 == array2"<<endl;
    

    vector<int> v1{1,2,3,4,5};
    vector<int> v2{1,2,3,4,5};
    if(v1 == v2)
    {
        cout<<"v1 == v2"<<endl;
    }
    const char* p1 = "hello";
    const char* p2 = "hello";
    printf("%p,%p",p1,p2);
    char arr1[] = "hello";
    char arr2[] = "hello";
    printf("%p,%p",arr1,arr2);
    cout<<endl;
    char arra1[] = "hello";
    char arra2[] = "world";
    char arra3[100] = {0};
    strcpy(arra3,arra1);
    strcat(arra3," ");
    strcat(arra3,arra2);
    cout<<arra3<<endl;

    return 0;
}
