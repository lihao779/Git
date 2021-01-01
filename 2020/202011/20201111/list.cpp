#include<algorithm>
#include <iostream>
#include <list>

using namespace std;


void TestList1()
{
    list<int> L1;
    list<int> L2(3,3);
    auto it = L2.begin();
    while(it!=L2.end())
    {
        cout<<*it<<" ";
        ++it;
    }
    cout<<endl;
    int array[3] = {1,2,3};
    list<int> L3(array,array+3);
    for(auto e:L3)
    {
        cout<<e<<" ";
    }
    cout<<endl;
    list<int> L4(L3);
    for(auto e:L4)
    {
        cout<<e<<" ";
    }
    cout<<endl;
    list<int> L5 {7,8,9};
    auto rit = L5.rbegin();
    while(rit!=L5.rend())
    {
        cout<<*rit<<" ";
        rit++;
    }
    cout<<endl;
}

void TestList2()
{
    list<int> L;
    L.push_back(1);
    L.push_back(2);
    L.push_back(3);
    L.push_back(4);
    L.push_back(5);

    cout<<L.front()<<endl;
    cout<<L.back()<<endl;
    cout<<L.size()<<endl;

    L.push_front(0);
    cout<<L.front()<<endl;

    L.pop_back();
    L.pop_front();
    cout<<L.front()<<endl;
    cout<<L.back()<<endl;
    
    L.insert(find(L.begin(),L.end(),3),9);
    
    L.erase(find(L.begin(),L.end(),9));
    L.erase(L.begin(),L.end());

    if(L.empty())
    {
       cout<<"empty"<<endl; 
    }
}

bool compare(int left,int right)
{
    return left>right;
}

void TestList3()
{
    list<int> L{1,2,3,2,4,5,5,3};
    L.sort(compare);
    for(auto e:L)
    {
        cout<<e<<" ";
    }
    cout<<endl;
    L.unique();
    for(auto e:L)
    {
        cout<<e<<" ";
    }
    cout<<endl;
}

bool IsEven(int date)
{
    return date%2==0;
}
void TestList4()
{
    list<int> L1{1,2,3,4,5};
    list<int> L2{2,3,4,7,8};
    L1.merge(L2);
    for(auto e:L1)
    {
        cout<<e<<" ";
    }
    cout<<endl;
    
    L1.reverse();
    for(auto e:L1)
    {
        cout<<e<<" ";
    }
    cout<<endl;
    L1.remove_if(IsEven);
    L1.remove(3);
    for(auto e:L1)
    {
        cout<<e<<" ";
    }
    cout<<endl;

}

void TestList5()
{
    list<int> L{1,2,3,4,5};
    auto it = L.begin();
    while(it!=L.end())
    {
        it = L.erase(it);
    }
    list<int> L1{1,2,3,4,5};
    auto it2 = L1.begin();
    L1.pop_back();
    cout<<*it2<<endl;
    L1.pop_front();
    cout<<*it2<<endl;
    cout<<L1.front()<<endl;

}
int main()
{
    // TestList1();
    // TestList2();
    // TestList3();
    // TestList4();
    TestList5();
    return 0;
}
