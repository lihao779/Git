#include <iostream>
#include <string>
#include <vector>

using namespace std;


size_t days[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
string month[12] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sept","Oct","Dec"};

class Date
{
    public:
        Date() = default;
        Date(const string& date);
        void Get()
        {
            cout << year_ << "/" << month_ << "/" << day_ << endl;
        }
    private:
        int year_;
        int month_;
        int day_;
};

int GetMonth(const string& date,size_t p)
{
    string s(date,0,p-1);
    for(int i = 0;i < 12;i++)
    {
        if(s == month[i])
        {
            return i+1;
        }
    }
    return -1;
}

Date::Date(const string& date)
{
    size_t p = 0;
    string number("1234567890");
    if((p = date.find_first_of(number)) > 0)
    {
        //月份名字格式
        //Jan 1 1900
        
        if(-1 == (month_= GetMonth(date,p)))
        {
            cout << "月份错误" << endl;
        }
        day_ = stoi(date.substr(date.find_first_of(" ") + 1));
        if(day_  > days[month_] && day_ < 0)
        {
            cout << "日期错误" << endl;
        }
        year_ = stoi(date.substr(date.find_last_of(" ") + 1));
    }
    else 
    {
        //日期格式
        day_ = stoi(date);
        month_ = stoi(date.substr(date.find_first_of("/") + 1));
        year_ = stoi(date.substr(date.find_last_of("/") + 1));
    }
}


int main()
{
    Date d1("Aug 1 1900");
    d1.Get();
    Date d2("1/2/1900");
    d2.Get();
    return 0;
}
