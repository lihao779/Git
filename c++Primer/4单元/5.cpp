#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> v1 = {1,2,3,4};
    vector<int> v2 = {1,2,3,4,5,6};
    int i = 0;
    int sz = (v1.size()>v2.size()?v2.size():v1.size());
    for(;i != sz; i++)
    {
        if(v1[i] != v2[i])
            break;
    }
    if(i == sz)
        cout << "is" <<endl;
    else
        cout << "not is"<<endl;
    return 0;
}
