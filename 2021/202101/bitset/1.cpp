#include <bitset>
#include <iostream>
#include "BitSet.hpp"
using namespace std;
int main()
{
    int array[] = {1,3,7,4,12,16,19,13,22,18};
    bite::bitset<23> bst;
    for(auto& e:array)
    {
        bst.set(e);
    }
    cout<<bst.count()<<endl;
    cout<<bst.size()<<endl;
    if(bst.test(12))
        cout<<"12 in bst"<<endl;
    else
        cout<<"12 not in bst"<<endl;
    bst.reset(12);
    if(bst.test(12))
        cout<<"12 in bst"<<endl;
    else
        cout<<"12 not in bst"<<endl;
    return 0;
}
