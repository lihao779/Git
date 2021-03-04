#include <iostream>



int binary_search(int array[],int size,int search_num)
{
    int left = 0;
    int right = size - 1;
    while(left <= right)
    {
        int mid = left + (right - left) / 2;
        if(search_num < array[mid])
            right = mid - 1;
        else if(search_num > array[mid])
            left = mid + 1;
        else
            return mid;
    }
    return -1;
}

int main()
{
    int search_num;
    std::cout << "please input search number:";
    std::cin >> search_num;
    int array[10] = {1,2,3,4,5,6,7,8,9,10};
    int index = binary_search(array,10,search_num);
    if(index < 0)
        std::cout << "not have " << search_num << std::endl;
    else
        std::cout << "have " << search_num << std::endl;

    return 0;
}
