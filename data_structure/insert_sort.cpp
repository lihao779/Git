#include <iostream>




int main()
{
    int array[10] = {9,8,7,6,5,4,3,2,1,0};
    /*
    for(int i = 1;i < 10;i++)
    {
        int key = array[i];
        //找位置 [0,i)
        int j = 0;
        for(;j < i;j++)
        {
            if(key <= array[j])
            {
                break;
            }
        }
        for(int m = i - 1;m >= j;m--)
        {
            array[m + 1] = array[m];
        }
        array[j] = key;
    }
    for(auto e : array)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;;
    */
    
    for(int i = 1;i < 10;i++)
    {
        int key = array[i];
        int j = i - 1;
        while((j >=0) && (key <= array[j]))
        {
            array[j+1] = array[j];
            j--;
        }
        array[j+1] = key;
    }
    for(auto e : array)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;;
    return 0;
}
