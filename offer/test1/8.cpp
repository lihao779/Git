#include <vector>
#include <string>
#include <iostream>
using namespace std;

int array[256];

int main()
{
    int result = 0;
    int j = 1;
    for(int i = 'a'; i <= 'z'; i++)
        array[i] = j++;

    string s;
    cin >> s;
    
    result = array[s[0]];
    for(size_t i = 1 ;i < s.size();i++)
    {
        result *= 26;
        result += array[s[i]];
    }

    cout << result << endl;
    return 0;
}
