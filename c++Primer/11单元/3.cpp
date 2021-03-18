#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

bool Islittle(int left, int right)
{
    return left < right;
}
bool Isbig(int left, int right)
{
    return left > right;
}

int main()
{
    typedef bool(*is) (int, int);
    vector<int> vec = {1, 2, 3, 4, 5, 6};
    multiset<int, is> iset(Isbig);
    iset.insert(vec.begin(), vec.end());
    for(auto& e: iset)
        cout << e << " ";
    cout << endl;
    return 0;
}
