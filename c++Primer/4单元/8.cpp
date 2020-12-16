#include <iostream>
#include <stdexcept>
using namespace std;

int main()
{
    int a;
    int b;
    while(cin>>a>>b)
    {
        try
        {
            if(b == 0)
                throw runtime_error("b is 0");
            cout<<a/b<<endl;
        }
        catch(runtime_error err)
        {
            cout<<err.what()<<endl;
            cout<<"Try again y or n?";
            char c;
            cin >> c;
            if(c == 'n')
                break;
        }
    }
    return 0;
}
