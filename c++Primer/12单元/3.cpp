#include <string>
#include <iostream>
#include <vector>
using namespace std;


vector<int>* Get()
{
    return new vector<int> ();
}
vector<int>* Set(vector<int>* p)
{
    int i = 5;
    int num = 0;
    while(i-- && cin >> num)
        p->push_back(num);
    return p;
}
void Print(vector<int>* p)
{
    for(size_t i = 0; i < p->size(); i++)
        cout << (*p)[i] << " ";
    cout << endl;
    delete p;
}



int main()
{
    const int* p1 = new const int(10);
    const string* p2 = new const string;
    delete p1;
    delete p2;
    Print(Set(Get()));
    return 0;
}
