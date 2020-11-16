#include<iostream>
#include<vector>

using namespace std;
#define ARRAYSIZE 4



void Test1()
{
    vector<int> v{4,3,2,6};
    vector<int> result(ARRAYSIZE);
    int max = 0;
    int sum =0,t = 0,n = ARRAYSIZE;
    for(size_t i = 0;i<v.size();i++)
    {
        sum+=v[i];
        t+=i*v[i];
    }
    result[0] = t;
    for(int i = 1;i<ARRAYSIZE;i++)
    {
        result[i] = t+sum-n*v[n-i];
        t = result[i];
    }
    max = result[0];
    for(size_t i = 1;i<result.size();i++)
    {
        if(max<result[i])
        {
            max = result[i];
        }
    }
    
    cout<<"最大值是"<<max<<endl;

}

int main()
{
    Test1();
    return 0;
}
