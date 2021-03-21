#include <string.h>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    const char* arr1= "hello";
    const char* arr2 = "world";
    char* p1 = new char[strlen(arr1) + strlen(arr2) + 1];
    strcpy(p1, arr1);
    strcat(p1, arr2);
    cout << p1 << endl;
    delete[] p1;


    string s1 = "hello";
    string s2 = "world";
    string* p2 = new string(s1 + s2);
    cout << *p2 << endl;
    delete p2;

    string s3;
    cin >> s3;
    char* p3 = new char[s3.size() + 1];
    strcpy(p3, s3.c_str());
    cout << p3 << endl;
    delete[] p3;
    return 0;
}
