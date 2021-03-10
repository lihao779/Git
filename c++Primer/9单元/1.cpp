
#include <iostream>
#include <vector>
#include <list>
using namespace std;


bool l_v_euqal(vector<int>& v,list<int>& l)
{
    //size相等
    //元素相等
    if(v.size() != l.size())
        return false;
    auto lb = l.begin();
    auto vb = v.begin();
    auto ve = v.end();
    while(vb != ve)
    {
        if(*vb != *lb)
            return false;
        vb++;
        lb++;
    }
    return true;
}


char IsBig(vector<int>& v,list<int>& l)
{
    //规定v大返回true，l大返回false
    //先判断那个size小，遍历，如果遍历途中有一个元素大则size小的大，否则另一个大
    char result = 'T';
    if(v.size() > l.size())
    {
        result = 'V';
        auto lb = l.begin();
        auto le = l.end();
        auto vb = v.begin();
        while(lb != le)
        {
            if(*lb > *vb)
            {
                result = 'L';
                break;
            }
            else if(*lb < *vb)
            {
                result = 'V';
                break;
            }
            lb++;
            vb++;
        }
    }
    else if(v.size() < l.size())
    {
        result = 'L';
        auto vb = v.begin();
        auto ve = v.end();
        auto lb = l.begin();
        while(ve != vb)
        {
            if(*vb > *lb)
            {
                result = 'V';
                break;
            }
            else if(*vb < *lb)
            {
                result = 'L';
                break;
            }
            vb++;
            lb++;
        }
    }
    else
    {
        
        auto vb = v.begin();
        auto ve = v.end();
        auto lb = l.begin();
        while(vb != ve)
        {
            if(*vb > *lb)
            {
                result = 'V';
                break;
            }
            else if(*vb < *lb)
            {
                result = 'L';
                break;
            }
            vb++;
            lb++;
        }
    }
    return result;
}

int main()
{
    vector<int> v1= {1,2,3,4};
    vector<int> v2 = {1,2,4};
    if(v2 > v1)
    {
        cout << "v2 > v1" << endl;
    }
    vector<int> v = {1,2,3,4,5};
    list<int> l1 = {1,2,3,4,5};
    list<int> l2 = {1,2,3,4};
    list<int> l3 = {1,2,3,4,6};
    list<int> l4 = {1,2,3,5,4};
    if(l_v_euqal(v,l1))
    {
        cout << "v == l1" << endl;
    }
    if(l_v_euqal(v,l2))
    {
        cout << "v == l2" << endl;
    }
    if(l_v_euqal(v,l3))
    {
        cout << "v == l3" << endl;
    }
    if(l_v_euqal(v,l4))
    {
        cout << "v == l4" << endl;
    }
    
    cout << IsBig(v,l1) << endl;
    cout << IsBig(v,l2) << endl;
    cout << IsBig(v,l3) << endl;
    cout << IsBig(v,l4) << endl;
    cout << "-------------------------------" << endl;

    list<string> lst;
    auto itbegin = lst.begin();
    string s;
    int i = 2;
    while(i-- && cin >> s)
    {
        itbegin = lst.insert(itbegin,s);
    }
    for(auto& e : lst)
    {
        cout << e << " ";
    }
    cout << endl;
    return 0;
}
