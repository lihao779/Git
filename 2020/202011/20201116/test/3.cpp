#include<queue>
#include<iostream>
#include<vector>
#include<functional>
#include<algorithm>
using namespace std;


/*
int main()
{
    std::priority_queue<int> q;
    q.push(1);
    q.push(2);
    cout<<q.top()<<endl;

    vector<int> v{1,2,3,4};
    priority_queue<int,vector<int>,greater<int>> q2(v.begin(),v.end());
    cout<<q2.top()<<endl;
    return 0;
}
*/

class Date
{
    public:
        Date(int year = 1900,int month = 1,int day = 1)
            :year_(year)
             ,month_(month)
             ,day_(day)
        {}
    bool operator<(const Date& d)const
    {
        return day_>d.day_;
    }
    int GetDay()const
    {
        return day_;
    }
    private:
        int year_;
        int month_;
        int day_;
};
void Test1()
{

    Date d1(2000,2,2);
    Date d2(2000,3,3);
    Date d0(2000,3,4);
    priority_queue<Date> d;
    d.push(d1);
    d.push(d0);
    d.push(d2);
}

class Greater
{
    public:
        bool  operator()(const Date* left,const Date* right)
        {
            return left->GetDay()>right->GetDay();
        }
};

void Test2()
{
    Date* p1 = new Date(2020,10,13);
    Date* p2 = new Date(2020,10,9);
    Date* p0 = new Date(2020,10,11);
    priority_queue<Date*,vector<Date*>,Greater> q;
    q.push(p1);
    q.push(p2);
    q.push(p0);
    cout<<q.top()<<endl;

}

void Test3()
{
    vector<int> v{2,5,7,8,9,6,4,3,1,0};
    sort(v.begin(),v.end(),greater<int>());//函数处需要类的实例化，模板处需要类名即可
    for(auto e:v)
    {
        cout<<e<<" ";
    }
    cout<<endl;
}

struct Good
{
    Good(const string& s,double price)
        :name_(s)
         ,price_(price)
    {}

    bool operator>(const Good& g)const
    {
        return price_>g.price_;
    }
    string name_;
    double price_;
};

class Greater1
{
    public:
    bool operator()(const Good& g1,const Good& g2)const
    {
        return g1.price_>g2.price_;
    }
};
void Test4()
{
    Good gz[] = {{"apple",1.8},{"banana",3.2},{"origin",2.2}};
    //sort(gz,gz+sizeof(gz)/sizeof(gz[0]),greater<Good>());
    sort(gz,gz+sizeof(gz)/sizeof(gz[0]),Greater1());
    for(auto e:gz)
    {
        cout<<e.name_<<" "<<e.price_<<endl;
    }

}

int main()
{
    // Test2();
    // Test3();
    Test4();
    return 0;
}
