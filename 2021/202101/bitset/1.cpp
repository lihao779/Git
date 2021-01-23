#include <bitset>
#include <iostream>

using namespace std;
int main()
{
    int array[] = {1,3,7,4,12,16,19,13,22,18};
    for(auto& e:array)
        e += 100;
    bitset<22> bst;
    for(auto& e:array)
    {
        bst.set(e-101);
    }
    cout<<bst.count()<<endl;
    cout<<bst.size()<<endl;
    if(bst.test(11))
        cout<<"12 in bst"<<endl;
    else
        cout<<"12 not in bst"<<endl;
    bst.reset(11);
    if(bst.test(11))
        cout<<"12 in bst"<<endl;
    else
        cout<<"12 not in bst"<<endl;
    return 0;
}
