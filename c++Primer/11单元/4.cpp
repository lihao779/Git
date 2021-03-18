#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <list>

using namespace std;

int main(int argc,char* argv[])
{
    if(argc != 2)
    {
        return -1;
    }
    ifstream in(argv[1]);
    if(!in)
    {
        cout << "打开文件错误" << endl;
        return -1;
    }
    map<string, list<int>> imap;
    string line_str;
    int line = 0;
    while(getline(in, line_str))
    {
        line++;
        //划分单词保存到imap中
        istringstream istr(line_str);
        string word;
        while(istr >> word)
        {
            imap[word].push_back(line);
        }
    }
    for(auto& e: imap)
        cout << e.first << " ";
    cout << endl;

    return 0;
}
