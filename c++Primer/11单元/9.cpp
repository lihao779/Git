#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

int main()
{
    multimap<string, string> imultimap;
    imultimap.insert({"lihao", "C++"});
    imultimap.insert({"lihao", "C"});
    int count = imultimap.count("lihao");
    auto fit = imultimap.find("lihao");
    auto bit = imultimap.begin();
    string name;
    while(bit != imultimap.end())
    {
        if(name == bit->first)
            cout << bit->second << " ";
        else
        {
            cout << endl;
            name = bit->first;
            cout << bit->first << ":" << bit->second << " ";
        }
        bit++;
    }
    

    while(count--)
        imultimap.erase(fit++);
    cout << imultimap.count("lihao") << endl;
    return 0;
}
