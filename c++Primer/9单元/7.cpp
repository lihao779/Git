
#include <iostream>

#include <string>

using namespace std;


int main()
{
    string str("helloworld");
    string s("ho");
    string maxstring;
    
    size_t pos1 = 0;
    size_t pos2 = 0;
    
    while(pos2 != string::npos )
    {
        pos1 = str.find_first_not_of(s,pos2);
        if(pos1 == string::npos)
        {
            break;
        }
        pos2 = str.find_first_of(s,pos1);
        if(pos1 == string::npos)
        {
            break;
        }
        else if(pos2 == string::npos)
        {
            
            if((str.size() - pos1 - 1) > maxstring.size())
            {
                maxstring = string(str.begin() + pos1,str.end());
            }
        }
        else
        {
            if((pos2 - pos1) > maxstring.size())
            {
                maxstring = string(str.begin() + pos1,str.begin() + pos2);

            }
        }
    }
    cout << maxstring << endl;
    return 0;

}

