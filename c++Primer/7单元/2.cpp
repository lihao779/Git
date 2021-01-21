#include <string>
#include <iostream>
using namespace std;

struct sale_date
{
    string ISBN;
    int count;
    int pricetotal;
};

int main()
{
    sale_date total;
    int price;
    if(cin >> total.ISBN >> total.count >> price)
    {
        total.pricetotal = total.count*price;
        sale_date temp;
        while(cin >> temp.ISBN>>temp.count >> price)
        {
            if(temp.ISBN == total.ISBN)
            {
                total.count += temp.count;
                total.pricetotal += temp.count* price;
            }
            else
            {
                cout<<"书名:"<<total.ISBN<<"   个数:"<<total.count<<"   单格:"<<total.pricetotal/total.count<<endl;
                total.ISBN = temp.ISBN;
                total.count = temp.count;
                total.pricetotal = temp.count*price;
            }
        }
        cout<<"书名:"<<total.ISBN<<"   个数:"<<total.count<<"   单格:"<<total.pricetotal/total.count<<endl;

    }
    else
    {
        cerr<<"No Date?"<<endl;
        return -1;
    }
    return 0;
}
