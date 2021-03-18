
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <utility>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

int main()
{
    map<string, int> word_count;
    string word;
    while(cin >> word)
    {
        auto ret = word_count.insert({word, 1});
        if(!ret.second)
            ret.first->second++;
    }
    return 0;
}
