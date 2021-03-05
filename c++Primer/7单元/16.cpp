#include <iostream>
#include <array>
#include <vector>
#include <list>

using namespace std;
int main()
{
    vector<int> vec1;
    vector<int> vec2(10);
    vector<int> vec3(10,0);
    vector<int> vec4(vec3);
    vector<int> vec5 = {1,2,3,4};
    vector<int> vec6(vec5.begin(),vec5.end()); 
    list<int> l(10,1);
    vector<int> vec7(10,1);
    vector<double> vec8(l.begin(),l.end());
    vector<double> vec9(vec7.begin(),vec7.end());
    vector<int> vec10(12);
    cout << vec7.size() << "-" << vec7.capacity() << endl;
    cout << vec10.size() << "-" << vec10.capacity() << endl;
    vec10 = vec7;
    cout << vec7.size() << "-" << vec7.capacity() << endl;
    cout << vec10.size() << "-" << vec10.capacity() << endl;
    vec10 = {1,2,3};
    std::array<int,10> arr = {1};
    for(auto e : arr)
        cout << e << " ";
    cout << endl;
    arr = {1,2};    
    for(auto e : arr)
        cout << e << " ";
    cout << endl;
    string s("Hello,world");
    s.assign(s.begin()+6,s.end());
    cout << s << endl;
    vector<int> vec11 = {1,2,3,4};
    vector<int> vec12 = {5,6,7,8,11};
    auto it = vec11.begin();
    //vec11.swap(vec12);
    vec11.assign(vec12.begin(),vec12.end());
    cout << *it << endl;
    vec11 = vec12;
    cout << *it << endl;
    string s1("hello");
    string s2("world");
    auto it1 = s1.begin();
    
    s1 = s2;
    //s1.swap(s2);
    cout << *it1 << endl;
    cout << "-------------------------------" << endl;
    list<string> l1;
    vector<const char*> vec13 = {"hello","world"};
    vec13.assign(vec13.cbegin(),vec13.cend());
    for(auto e : vec13)
        cout << e << " ";
    cout << endl;
    list<const char*> l2 = {"hello","world"};
    vector<string> vec14(l2.cbegin(),l2.cend());






    string s3("1");
    string s4(10000,'2');
    auto it2 = s3.begin();
    s3.swap(s4);
    cout << *it2 << endl;
    while(it2 != s4.end())
    {
        cout << *it2 << " ";
        it2++;
    }
    cout << endl;
    string s5;
    cout << s5.capacity() << endl;
    cout << sizeof(s5) << endl;
    return 0;
}
