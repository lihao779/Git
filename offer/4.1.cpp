#include <iostream>


int main()
{
    int array1[20] = {1, 3, 5, 7, 9};
    int array2[5] = {2, 4, 6, 8, 10};
        
    int sumnum = 9;
    int arrnum1 = 4;
    int arrnum2 = 4;

    while(arrnum1 < 0 || arrnum2 < 0 )
    {
        if(arrnum1 >= 0 && arrnum2 >= 0 && array1[arrnum1] > array2[arrnum2])
        {
            array1[sumnum] = array1[arrnum1];
            sumnum--;
            arrnum1--;
        }
        else if(arrnum1 >= 0 && arrnum2 >= 0 && array1[arrnum1] <= array2[arrnum2])
        {
            array1[sumnum] = array2[arrnum2];
            sumnum--;
            arrnum2--;
        }
    }
    
    while(arrnum2 >= 0)
    {
        array1[sumnum--] = array2[arrnum2--];
    }
    
    for(auto e: array1)
        std::cout << e << " ";

    return 0;
}
