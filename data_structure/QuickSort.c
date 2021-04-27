#include <stdio.h>



void swap(int* left, int* right)
{
    int temp = *left;
    *left = *right;
    *right = temp;
}

int Parition(int* data, int length, int start, int end)
{
    if(data == NULL || length <= 0 || start < 0 || end >= length)
        return -1;
   
    int small = end;
  
    while(start < small)
    {
        while(start < small && data[start] <= data[end])
            start++;
        while(start < small && data[small] >= data[end])
            small--;
        if(start < small)
            swap(&data[small], &data[start]);
    }
    if(start != end)
        swap(&data[start], &data[end]);
    return start;
}


void QuickSort(int* data, int length, int start, int end)
{
    if(start == end)
        return;
    int index = Parition(data, length, start, end);
    if(start < index)
        QuickSort(data, length, start, index - 1);
    if(index < end)
        QuickSort(data, length, index + 1, end);
}


int main()
{
    int data[] = {1, 3, 5, 8, 5, 6, 3};
    int sz = sizeof(data) / sizeof(int);
    QuickSort(data, sz, 0, sz - 1);
    for(int i = 0; i < sz; i++)
        printf("%d ",data[i]);
    printf("\n");
    return 0;
}
