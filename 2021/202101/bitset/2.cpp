#include <iostream>
#include <bitset>
#include <string>
using namespace std;

int main()
{
    unsigned int a = 12345678;
    bitset<32> bst(a);
    cout<<bst.to_string()<<endl;
    string strbinary("00111100");
    bitset<8> bst1(strbinary);
    cout<<bst1.to_ulong()<<endl;
    return 0;
}
