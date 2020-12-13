#include <iostream>
using namespace std;


int Find(int* array,int size,int num)
{
    int left = 0;
    int right = size;
    int mid = left + ((right - left) >> 1);
    while(left < right)
    {
        if(array[mid] == num)
            break;
        else if(array[mid] < num)
        {
            left = mid+1;
        }
        else 
            right = mid;
        mid = left + ((right - left) >> 1);
    }
    if(left == right)
        return -1;
    return mid;
}

int main()
{

    int array[] = {1,2,3,4,5,6,7,8,9};
    int mid = Find(array,sizeof(array)/sizeof(int),10);
    cout<<mid<<endl;
    if(mid != -1)
    cout<<array[mid]<<endl;
    return 0;
}
