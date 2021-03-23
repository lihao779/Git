#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <unordered_map>
#include <string>

using namespace std;

map<string, string> buildMap(ifstream& map_file)
{
    //unordered_map<string, string> imap;
   map<string, string> imap;
    string s;
    while(getline(map_file, s))
    {
        size_t index = s.find(' ');
        string key(s.begin(), s.begin() + index);
        string val(s.begin() + index + 1, s.end());
        imap.insert({key, val});
    }
    return imap;
}


void word_transform(ifstream& map_file, ifstream& input)
{
    auto word_map = buildMap(map_file);
    string result;
    string word;
    while(getline(input, word)) 
    {
        istringstream istr(word);
        string temp;
        while(istr >> temp)
        {
            if(word_map.find(temp) != word_map.end())
                result += word_map[temp];
            else
            {
                result += temp;
            }
            result += " ";
        }
    }
    cout << result << endl;
}

int main()
{
    ifstream map_file("t1.txt");
    ifstream file("t2.txt");
    word_transform(map_file, file);
    return 0;
}
