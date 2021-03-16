#include <unistd.h>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

int main()
{
    //vector<int> vec;
    //istream_iterator<int> in_it(cin);
    //istream_iterator<int> eof;
    //while(in_it != eof)
    //    vec.push_back(*in_it++);
    //for(auto& e: vec)
    //    cout << e << " ";
    //cout << endl;
    //istream_iterator<int>  in_it1(cin), eof1;
    //cout << "111" << endl;
    //sleep(3);
    //vector<int> vec1(in_it1,eof1); 
    //for(auto& e: vec1)
    //    cout << e << " ";
    //cout << endl;
    //ostream_iterator<int> os_it(cout, " ");
    //vector<int> vec3 = {1, 2, 3, 4, 5, 6};
    //for(auto& e: vec3)
    //    *os_it++ = e;
    //cout << endl;
    vector<int> vec4;
    istream_iterator<int> is_it(cin), eof;
    ostream_iterator<int> os_it(cout, " ");
    while(is_it != eof)
        vec4.push_back(*is_it++);
    sort(vec4.begin(),vec4.end());
    copy(vec4.begin(),vec4.end(),os_it);
    cout << endl;
    unique_copy(vec4.begin(),vec4.end(),os_it);
    cout << endl;
    return 0;
}
