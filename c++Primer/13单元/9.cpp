#include <iostream>
#include <vector>
using namespace std;

int f();

int main()
{
    vector<int> v(100);
    int&& ra1 = f();    
    int&  ra2 = v[0];
    int&  ra3 = ra1;
    int&& ra4 = v[0] * f();
    return 0;
}
