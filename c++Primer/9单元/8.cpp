#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    vector<string> vec;
    
    vec.push_back("1");
    vec.push_back("2");
    vec.push_back("3");
    vec.push_back("4");
    vec.push_back("5");
    vec.push_back("6");
    vec.push_back("7");
    vec.push_back("8");
    vec.push_back("9");
    vec.push_back("10");


    double sum = 0;
    for(size_t i = 0;i < vec.size();i++)
    {
        sum += stod(vec[i],0);
    }
    cout << sum << endl;
    cout << 1.0 << endl;
    return 0;

}
