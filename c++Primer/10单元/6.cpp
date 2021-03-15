#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


void fun1()
{
    size_t v1 = 2;
    auto f1 = [v1]()mutable{return ++v1;};
    v1 = 0;
    cout << f1() << endl;
}


int main()
{
    //fun1();
    vector<int> vec{-1,-2,4,5,7,-10};
    transform(vec.begin(),vec.end(),vec.begin(),[](int ele) -> int
                                                {if(ele > 0) return ele;else return -ele;});
    for(auto e : vec)
        cout << e << " ";
    cout << endl;
    size_t count = count_if(vec.begin(),vec.end(),[](int ele)
                                    {return ele > 0;});
    cout << count << endl;
    //auto f1 = [count]()mutable
    //            {
    //                if(!count) return true;
    //                while(--count);
    //                return false;
    //            };
    auto f1 = [&count]
                {
                    if(!count) return true;
                    while(--count);
                    return false;
                };
    if(f1())
    {
        cout << "捕获变量是0" << endl;
    }
    else
    {
        cout << "捕获变量不是0" << endl;
    }
    cout << count << endl;
    return 0;

}
