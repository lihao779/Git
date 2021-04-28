

int traversal(int* data, int size)
{
    int min = data[0];
    for(int i = 0; i < size; i++)
    {
        if(data[i] < min)
            min = data[i];
    }
    return min;
}

int minarr(int* data, int size)
{
    if(data[0] < data[size - 1])
        return data[0];
    int start = 0;
    int end = size - 1;

    while(end - start > 1)
    {
        int mid = start + (end - start) / 2;
        if(data[mid] == data[start] && data[start] == data[end])
            return traversal(data, size);
        else if(data[mid] >= data[start])
            start = mid;
        else
            end = mid;
    }
    return data[end];
}

#include <stdio.h>
int main()
{
    int data[] = {1, 2, 4, -1 , 0};
    printf("%d\n",minarr(data, 5));
    return 0;
}
