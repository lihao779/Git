#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    vector<string> v;
    v.push_back("now");
    v.push_back("now");
    v.push_back("now");
    v.push_back("new");
    v.push_back("new");
    
    auto it = v.begin();
    int ret = 1;
    int max = 0;
    while(it+1 != v.end())
    {
        if(!(*it).compare(*(it+1)))
        {
            ++ret;
        }
        else 
        {
            if(ret > max)
                max = ret;
            ret = 1;
        }
        ++it;
    }
    if(ret > max)
       max = ret;
    cout << max << endl;



    return 0;
}
