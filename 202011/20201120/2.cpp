#include<iostream>
#include<vector>

using namespace  std;

int main()
{
    vector<int> v{1,2,3,4,5,6,7,8,9};
    auto it_begin = v.begin();
    auto it_end = v.end();
    auto it_mid = it_begin+(it_end-it_begin)/2;
    int date = 1;
    while(it_mid!=it_end && date!=*it_mid)
    {
       if(*it_mid>date)
       {
           it_end = it_mid;
       }
       else
       {
           it_begin = it_mid+1;
       }
       it_mid = it_begin+(it_end-it_begin)/2;
    }

    cout<<*it_mid<<endl;
    return 0;
}
