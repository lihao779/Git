#include <iostream>
#include <stdexcept>
using namespace std;
int main()
{
    int a = 2;

    cout << "input a:";
    while(cin >> a)
    {
    try
    {
        if(a == 1)
            cout << "a == 1"<<endl;
        else     
        throw runtime_error("1 != 2");
    } 
    catch(runtime_error err)
    {
        cout<<err.what();
        cout << "Try again y or n?"<<endl;
        char c;
        cin >> c;
        if(c == 'y')
        cout << "input a:";
        else 
            break;
    }
    }
    return 0;
}
