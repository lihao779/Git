
#include <unistd.h>
#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    ifstream in("test.txt");
    istream_iterator<string> is_it(in), eof;
    vector<string> vec;
    while(is_it != eof)
        vec.push_back(*is_it++);
    ostream_iterator<string> os_it(cout, " ");
    for(auto& e: vec)
        *os_it++ = e;
    cout << endl;
    
    return 0;
}

