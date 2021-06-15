#include <iostream>
#include <vector>
using namespace std;

int find(int* array, int left, int right, int num)
{
    while(left <= right)
    {
        int mid = left + ((right - left) >> 1);
        if(array[mid] == num)
            return mid;
        else if(array[mid] > num)
            right = mid - 1;
        else
            left = mid + 1;
    }

    return -1;
}

int find1(const vector<int>& v, int num)
{
    int left = 0, right = v.size() - 1;

    while(left <= right)
    {
        int mid = left + ((right - left) >> 1);
        if(v[mid] == num)
            return mid;
        else if(v[mid] > num)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return -1;
}
int find2(const vector<int>& v, int num)
{
    int left = 0, right = v.size();
    
    while(left < right)
    {
        int mid = left + ((right - left) >> 1);
        if(v[mid] == num)
            return mid;
        else if(v[mid] > num)
            right = mid;
        else 
            left = mid + 1;
    }
    return -1;
}


int main()
{
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int findnum = 0;
    cin >> findnum;
    int index = find(array, 0, sizeof(array)/sizeof(array[0]), findnum);
    if(index == -1)
        cout << "not find " << findnum << endl;
    else
        cout << "find " << findnum << " index is " << index << endl;
    return 0;
}
