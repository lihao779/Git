#include <unistd.h>
#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <fstream>

using namespace std;

bool func(string source,string odd,string even)
{
    if(!source.size() || !odd.size() || !even.size())
        return false;
    ifstream in(source);
    ofstream out_odd(odd);
    ofstream out_even(even);
    vector<int> vec;
    istream_iterator<int> is_it(in), eof;
    while(is_it != eof)
        vec.push_back(*is_it++);
    ostream_iterator<int> os_odd(out_odd, "\n");
    ostream_iterator<int> os_even(out_even, "\n");
    for(auto& e: vec)
    {
        if(e & 1)
            *os_odd++ = e;
        else
            *os_even++ = e;
    }
    return true;
}

int main()
{
    string source = "source.txt";
    string odd = "odd.txt";
    string even = "even.txt";
    if(func(source, odd, even))
        cout << "写入成功" << endl;
    else
        cout << "写入失败" << endl;
    return 0;
}
