#include<unistd.h>
#include<algorithm>
#include<iostream>
#include<vector>
#include<stdio.h>
#include<string>

using namespace std;

void TestVector1()
{
    vector<int> v1;
    vector<int> v2(10,5);
    
    int array[] = {1,2,3,4};
    vector<int> v3(array,array+sizeof(array)/sizeof(array[0]));

    size_t i = 0;
    for(i = 0;i<v1.size();i++)
    {
        cout<<v1[i]<<" ";
    }
    cout<<endl;

    for(i = 0;i<v2.size();i++)
    {
        cout<<v2[i]<<" ";
    }
    cout<<endl;

    for(i = 0;i<v3.size();i++)
    {
        cout<<v3[i]<<" ";
    }
    cout<<endl;

    string s("hello");
    vector<char> v4(s.begin(),s.end());

    vector<int> v5(v3);

    //vector<int> v6{1,2,3,4};
    for(i = 0;i<v4.size();i++)
    {
        cout<<v4[i]<<" ";
    }
    cout<<endl;
    for(i = 0;i<v5.size();i++)
    {
        cout<<v5[i]<<" ";
    }
    cout<<endl;

}

void TestVector2()
{
    int array[] = {1,2,3,4};
    vector<int> v1(array,array+sizeof(array)/sizeof(array[0]));
    vector<int>::iterator it =v1.begin();
    while(it!=v1.end())
    {
        cout<<*it<<" ";
        ++it;
    }
    cout<<endl;
    vector<int>::reverse_iterator rit = v1.rbegin();
    while(rit!=v1.rend())
    {
        cout<<*rit<<" ";
        rit++;
    }
    cout<<endl;
    for(auto e:v1)
    {
        cout<<e<<" ";
    }
    cout<<endl;
}

void TestVector3()
{
    vector<int> v{1,2,3,4,5,6,7,8};
    cout<<v.size()<<endl;
    cout<<v.capacity()<<endl;

    if(v.empty())
    {
        cout<<"v empty"<<endl;
    }
    else
    {
        cout<<"v not empty"<<endl;
    }
    v.clear();
    cout<<v.size()<<endl;
    cout<<v.capacity()<<endl;
    
}
void TestVector4()
{
    vector<int> v{1,2,3,4,5,6,7,8,9,0};
    cout<<v.size()<<endl;
    cout<<v.capacity()<<endl;
    for(auto e:v)
    {
        cout<<e<<" ";
    }
    cout<<endl;


    v.resize(5);
    cout<<v.size()<<endl;
    cout<<v.capacity()<<endl;
    for(auto e:v)
    {
        cout<<e<<" ";
    }
    cout<<endl;
    
    
    v.resize(7,100);
    cout<<v.size()<<endl;
    cout<<v.capacity()<<endl;
    for(auto e:v)
    {
        cout<<e<<" ";
    }
    cout<<endl;
    
    v.resize(9);
    cout<<v.size()<<endl;
    cout<<v.capacity()<<endl;
    for(auto e:v)
    {
        cout<<e<<" ";
    }
    cout<<endl;
    
    
    
    v.resize(20);
    cout<<v.size()<<endl;
    cout<<v.capacity()<<endl;
    for(auto e:v)
    {
        cout<<e<<" ";
    }
    cout<<endl;
    
}

void TestVector5()
{
    vector<char> v{'1','2'};
    cout<<v.capacity()<<endl;
    v.reserve(5);
    cout<<v.capacity()<<endl;
    v.reserve(30);
    cout<<v.capacity()<<endl;
    v.reserve(10);
    cout<<v.capacity()<<endl;
    v.reserve(20);
    cout<<v.capacity()<<endl;
    v.reserve(40);
    cout<<v.capacity()<<endl;
}
void TestVector6()
{
    vector<int> v{1,2,3,4,5,6,7,8,9,0};
    cout<<v.front()<<endl;
    cout<<v.back()<<endl;
    v.clear();
    cout<<v.size()<<endl;
    cout<<v.capacity()<<endl;
    cout<<v.front()<<endl;
    cout<<v.back()<<endl;

}
void TestVector7()
{
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.pop_back();
    v.insert(v.begin(),0);
    
    v.insert(find(v.begin(),v.end(),2),10,5);

    int array[] = {9,8,7,6};
    v.insert(v.end(),array,array+sizeof(array)/sizeof(array[0]));
    for(auto e:v)
    {
        cout<<e<<" ";
    }
    cout<<endl;
}

class A
{
    public:
    A(int a = 10)
        :_a(a)
    {}
    A(const A&a)
        :_a(a._a)
    {
        cout<<"A(const& a)"<<endl;
    }

    private:
        int _a;
};

void TestVector8()
{
    A a;
    vector<A> v;
    v.push_back(a);
    v.reserve(10);
    v.push_back(a);
    v.push_back(a);

}
void TestVector9()
{
    vector<int> v1{0,1,2,3,4,5};
    vector<int> v2{6,7,8,9,10};
    cout<<v1.size()<<endl;
    cout<<v2.size()<<endl;
    cout<<v1.capacity()<<endl;
    cout<<v2.capacity()<<endl;
    for(auto e:v1)
    {
        cout<<e<<" ";
    }
    cout<<endl;
    for(auto e: v2)
    {
        cout<<e<<" ";
    }
    cout<<endl;
    v1.swap(v2);

    cout<<v1.size()<<endl;
    cout<<v2.size()<<endl;
    cout<<v1.capacity()<<endl;
    cout<<v2.capacity()<<endl;
    for(auto e:v1)
    {
        cout<<e<<" ";
    }
    cout<<endl;
    for(auto e: v2)
    {
        cout<<e<<" ";
    }
    cout<<endl;
}
void TestVector10()
{
    vector<int> v{1,2,3,4,5,6,7,8,9,0};
    for(auto e:v)
    {
        cout<<e<<" ";
    }
    cout<<endl;
    v.erase(v.begin());
    for(auto e:v)
    {
        cout<<e<<" ";
    }
    cout<<endl;
    v.erase(v.begin(),v.begin()+3);
    for(auto e:v)
    {
        cout<<e<<" ";
    }
    cout<<endl;
    v.erase(v.begin(),v.end());
    for(auto e:v)
    {
        cout<<e<<" ";
    }
    cout<<endl;
}

void TestVector11()
{
    vector<int> v{1,2,3,4,5,6,7,8,9,0};

    v.erase(v.begin());
    v.erase(v.begin(),v.begin()+3);
    auto it = v.begin();
   //v.erase()会导致迭代器失效，删除之后不能使用
    /*while(it!=v.end())
    {
        v.erase(it);
        it++;
    }*/
    //-----------修改-----
    while(it!=v.end())
    {
        it = v.erase(it);
    }
}

void TestVector12()
{
    vector<int> v1{1,2,3,4};
    vector<int> v2{5,6,7,8,9};
    //it1 为原来v1空间首地址
    //swap后v1.end()的位置已经是原v2.end()的地址两者不能匹配---所以while乱套
    auto it1 = v1.begin();
    auto it2 = v2.begin();

    v1.swap(v2);
    /*
     *------加这两行即可正确
     it1 = v1.begin();
     it2 = v2.begin();
     */
    cout<<*it1<<endl;
    cout<<*it2<<endl;

    while(it1!=v1.end())
    {
        cout<<*it1<<" ";
    }
    cout<<endl;
}

void TestVector13()
{
    vector<int> v{1,2,3,4};
    auto it = v.begin();
    v.erase(it);
    cout<<*(it)<<endl;
}

void TestVector14()
{
    vector<vector<int>> v;
    vector<int> vv(5,10);
    for(int i = 0;i<4;i++)
    {
        v.push_back(vv);
    }

    vector<vector<int>> vvv(4,vector<int>(5,10));
    for(int i = 0;i<4;i++)
    {
        for(int j = 0;j<5;j++)
        {
            cout<<vvv[i][j]<<" ";
        }
        cout<<endl;
    }
}

/*
 * 杨辉三角
 * 1
 * 1 1
 * 1 2 1
 * 1 3 3 1
 * 1 4 6 4 1
 */


void TestVector15(int n)
{
    vector<vector<int>> vv;
    vv.resize(n);
    for(int i = 0;i<n;++i)
    {
        vv[i].resize(i+1,1);
    }

    for(size_t i = 2;i<vv.size();i++)
    {
        for(size_t j =1;j<vv[i].size()-1;j++)
        {
            vv[i][j] = vv[i-1][j-1]+vv[i-1][j];
        }
    }

    for(size_t i = 0;i<vv.size();i++)
    {
        for(size_t j = 0;j<vv[i].size();j++)
        {
            printf("%-3d ",vv[i][j]);
            //cout<<vv[i][j]<<" ";
        }
        cout<<endl;
    }
}

int main()
{
    // TestVector1();
    // TestVector2();
    // TestVector3();
    // TestVector4();
    // TestVector5();
    // TestVector6();
    // TestVector7();
    // TestVector8();
    // TestVector9();
    // TestVector10();
    // TestVector11();
    // TestVector12();
    // TestVector13();
    // TestVector14();
    TestVector15(10);
    return 0;
}
/*
----------------扩容的操作都可能导致迭代器失效----------------
resize(),reserve(),assign(),push_back(),insert()
--------------------------------------------------------------
swap(),clear(),也可能导致迭代器失效
--------------------特别的erase()也会导致迭代器失效-----------
--------------------------------------------------------------
==============================================================
处理方法：
         每次给迭代器重新赋值

*/
