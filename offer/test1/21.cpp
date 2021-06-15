#include <iostream>

using namespace std;

bool Is_commplete_square(int x)
{
    int left = 0, right = x;
    while(left <= right)
    {
        int mid = left + ((right - left) >> 1);
        if(mid*mid == x)
            return true;
        else if(mid*mid < x)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return false;
}


int main()
{
    int n;
    while(cin >> n)
    {
        if(Is_commplete_square(n))
            cout << n <<" is commplete square" << endl;
        else
            cout << n <<" is not commplete square" << endl;
    }
    return 0;
}
