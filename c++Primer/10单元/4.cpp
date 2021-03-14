#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <string>
using namespace std;

bool IsBig_five(string& s)
{
    return s.size() >=5 ? true : false;
}

int main()
{
    vector<string> vec{"123","12345","1231231","222","12331"};
    //vector<string>::iterator it_end = partition(vec.begin(),vec.end(),IsBig_five);
    vector<string>::iterator it_end = partition(vec.begin(),vec.end(),[](string & s) -> bool
                                                                        {   return s.size() >= 5;});
    for(auto it = vec.begin();it != it_end;it++)
    {
        cout << *it << " ";
    }
    cout << endl;
    return 0;
}
