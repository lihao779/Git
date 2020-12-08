#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<vector<int> > v(5,vector<int>(6,8));
    for(auto e:v)
    {
        for(auto ee:e)
        {
            cout<<ee<<" ";
        }
        cout<<endl;
    }
    return 0;
}
