#include <iostream>
#include <vector>
using namespace std;


int sport(int x)
{
    int left = 0, right = x;
    while(right - left > 1)
    {
        int mid = left + ((right - left) >> 1);
        if(mid*mid == x)
            return mid;
        else if((mid*mid) < x)
            left = mid;
        else
            right = mid - 1;
    }

    if(right*right <= x)
        return right;
    else
        return left;
}


int main()
{
    int n = 8;
    cout << sport(n);
    return 0;
}
