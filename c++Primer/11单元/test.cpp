#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
bool Isleap(int year)
{
    if(year%4 == 0 && year%100 != 0)
        return true;
    else if(year%400 == 0)
        return true;
    return false;
}

struct info
{
    info() = default;
    info(int time,int money,bool status)
    {
        time_ = time;
        money_ = money;
        status_ = status;
    }
    int time_;
    int money_;
    bool status_;//规定true买入，false卖出
};
double rata = 0.5;


void caltime(int time, int& year, int& month, int& day)
{
    string str;
    while(time)
    {
        str.push_back(time%10 + 48);
        time /= 10;
    }
    reverse(str.begin(), str.end());
    //str = to_string(time);
    year = stoi(str.substr(0, 4));
    month = stoi(str.substr(4, 2));
    day = stoi(str.substr(6, 2));
}
int calday(const int start_year,const int start_month, const int start_day, const int end_year, const int end_month, const int end_day)
{
    if(start_year > end_year || (start_year == end_year && start_month > end_month) || (start_year == end_year && start_month == end_month && start_day > end_day))
        return -1;
    int day = 0;
    if(start_year == end_year)
    {
        if(start_month == end_month)
            day =  end_day - start_day;
        else
        {
            for(int i = start_month; i < end_month; i++)
            {
                if(i == 2 && Isleap(start_year))
                    day += 29;
                else 
                    day += days[i];
            }
            day -= start_day;
            day += end_day;
        }
    }
    else
    {
        for(int i = start_year; i < end_year; i++)
        {
            if(Isleap(start_year))
                day += 366;
            else
                day += 365;
        }
        for(int i = 1; i < start_month ; i++)
        {
            if(i == 2 && Isleap(start_year))
                day -= 29;
            else
                day -= days[i];
        }
        day -= start_day;
        for(int i = 1; i < end_month; i++)
        {
            if(i == 2 && Isleap(start_year))
                day += 29;
            else
                day += days[i];
        }
        day += end_day;
    }
    return day; 
}

int main()
{
    vector<info> arr;
    arr.push_back(info(20201001,100,true));
    arr.push_back(info(20201101,100,false));
    arr.push_back(info(20201201,100,true));
    arr.push_back(info(20210101,100,true));
    arr.push_back(info(20210201,100,true));
    double money_in = 0;
    double money_out = 0;
    int start_year = 0;
    int end_year = 0;
    int start_month = 0;
    int end_month = 0;
    int start_day = 0;
    int end_day = 0;
    //核心---
    //从第二个节点开始算起
    //1.计算天数
    //2.判断是否为买入
    //    是----更新在里面存的钱数
    //           （注意在里面存的钱分为三部分，
    //                  第一部分是上个月在里面存的，
    //                  第二部分是之前就有的
    //                  第三部分是之前第一部分和第二部分产生的利息
    //    否---更新在里面存的钱&保存取出来的钱
    for(size_t i = 1;i < arr.size(); i++)
    {
        //计算天数
        int start = arr[i-1].time_;
        caltime(start,start_year, start_month, start_day);
        int end = arr[i].time_;
        caltime(end,end_year, end_month, end_day);
        int all_day = calday(start_year, start_month, start_day, end_year, end_month, end_day);
        //判断是否为买入
        //   是-算出利息，更新在里面存的钱的数目
        //   否-算出利息，更新在里面存的钱的数目，更新取出钱的数目
        if(arr[i-1].status_)
        {
            //买入
            money_in = money_in + arr[i-1].money_ + (money_in + arr[i-1].money_) * rata * all_day;
        }
        else
        {
            //卖出
            money_out += arr[i-1].money_;
            money_in = money_in - arr[i-1].money_ + (money_in - arr[i-1].money_) * rata * all_day;
        }
    }

    return 0;
}
