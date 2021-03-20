#include <string>
#include <iostream>
#include <vector>
#include <memory>
using namespace std;


shared_ptr<vector<int>> Get()
{
    return make_shared<vector<int>>();
}
shared_ptr<vector<int>> Set(shared_ptr<vector<int>> p)
{
    int i = 5;
    int num = 0;
    while(i-- && cin >> num)
        p->push_back(num);
    return p;
}
void Print(shared_ptr<vector<int>> p)
{
    for(size_t i = 0; i < p->size(); i++)
        cout << (*p)[i] << " ";
    cout << endl;
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
