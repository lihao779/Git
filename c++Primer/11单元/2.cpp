#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

class family
{
    family() = default;
    bool insertnewsur(const string& surname, vector<string>& number)
    {
        return fam_.insert({surname, number}).second;
    }
    bool insertnumber(const string& surname, const string& number)
    {
        fam_[surname].push_back(number);
        return true;
    }
    private:
        map<string,vector<string> > fam_;
};


int main()
{
    vector<int> vec;
    int num;
    int count = 5;
    while(count-- && cin >> num)
    {
        size_t i;
        for(i = 0;i < vec.size(); i++)
        {
            if(vec[i] == num)
                break;
        }
        if(i == vec.size())
            vec.push_back(num);
    }
    for(auto& e: vec)
        cout << e << " ";
    cout << endl;

    return 0;
}
