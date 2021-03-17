#include <map>
#include <iostream>
#include <string>
#include <set>
using namespace std;

int main()
{
    map<string,size_t> word_count;
    set<string> exclude = {"The", "world"};
    string word;
    int count = 5;
    while(count-- && cin >> word)
    {
        int size = word.size() - 1;
        if(word[size] == ',' || word[size] == '.')
            word.erase(size);
        if(exclude.find(word) == exclude.end())
            word_count[word]++;
    }
    for(auto& e: word_count)
        cout << e.first << " occurs " << e.second << (e.second > 1? " times": " time") << endl;
    return 0;
}
