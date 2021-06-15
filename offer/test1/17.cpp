

int Findfirstk(int* array, int start, int end, int length, int k)
{
    if(length < 0)
        return -1;
    if(start > end)
        return -1;
    int mid = start + ((end - start) >> 1);
    if(array[mid] == k && (mid == 0 || array[mid - 1] != k))
        return mid;
    else if(array[mid] == k && array[mid - 1] == k)
        return Findfirstk(array, start, mid - 1, length, k);
    else if(array[mid] > k)
        return Findfirstk(array, start, mid - 1, length, k);
    else
        return Findfirstk(array, mid + 1, end, length, k);
}
int Findlastk(int* array, int start, int end, int length, int k)
{
    if(length < 0)
        return -1;
    if(start > end)
        return -1;
    int mid = start + ((end - start) >> 1);
    if(array[mid] == k && (mid == length - 1 || array[mid + 1] != k))
        return mid;
    else if(array[mid] == k && array[mid + 1] == k)
        return Findlastk(array, mid + 1, end, length, k);
    else if(array[mid] > k)
        return Findlastk(array, start, mid - 1, length, k);
    else
        return Findlastk(array, mid + 1, end, length, k);
}
#include <iostream>
using namespace std;
int main()
{
    int array[] = {1, 2, 3, 3, 3, 4, 5};
    int start = 0;
    int end = sizeof(array)/sizeof(array[0]);
    for(int i = 0; i < end; ++i)
    {
        cout << array[i] << " ";
    }
    cout << endl;
    int k;
    cin >> k;
    int firstkindex = Findfirstk(array, start, end - 1, end, k);
    int lastkindex = Findlastk(array, start, end - 1, end, k);
    if(firstkindex != -1 && lastkindex != -1)
        cout << "array have " << k << " number: " <<lastkindex - firstkindex + 1 << endl;
    else
        cout << "array have " << k << " number: " << 0 << endl;

    return 0;
}
