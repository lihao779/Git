#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <utility>

using namespace std;

int main()
{
    string str;
    string number;
    vector<int> vec_num;
    vector<string> vec_str;
    string temp1;
    char temp2;
    vector<pair<string, int> > pair_;
    getline(cin, str);
    getline(cin, number);
    istringstream ist1(str);
    istringstream ist2(number);
    while(ist1 >> temp1)
        vec_str.push_back(temp1);
    while(ist2 >> temp2)
        vec_num.push_back(temp2 - '0');
   
    for(size_t i = 0; i < vec_str.size(); i++)
    {
        if(i < vec_num.size())
            pair_.push_back(pair<string,int> (vec_str[i], vec_num[i]));
        else
            pair_.push_back(pair<string,int> (vec_str[i], 0));

    }
    for(auto& e: pair_)
        cout << e.first << "-" << e.second << " ";
    cout << endl;
    return 0;
}
