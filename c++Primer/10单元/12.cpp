#include <unistd.h>
#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <fstream>
#include <list>
#include <algorithm>
using namespace std;

int main()
{
    vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto rit = vec.crbegin();
    while(rit != vec.crend())
        cout << *rit++ << " ";
    cout << endl;
    auto it = vec.cbegin();
    while(it != vec.cend())
        cout << *it++ << " ";
    cout << endl;
    list<int> l  = {1, 2, 3, 4, 0, 10};
    auto fit = find(l.cbegin(),l.cend(),0) ;
    fit == l.end() ? cout << "不存在0这个元素" << endl : cout << *fit << endl;
    vector<int> vec1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int>::reverse_iterator rb(vec1.begin() + 7);
    vector<int>::reverse_iterator re(vec1.begin() + 2);
    while(re != rb)
        cout << *rb++ << " ";
    cout << endl;
    return 0;
}
