#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> dest = {2, 4, 5, 8, 10};
    vector<int> src = {1, 3, 5, 7};

    int destsize = dest.size();
    int srcsize = src.size();
    int sumsize = destsize + srcsize;
    dest.resize(sumsize);

    while(destsize >= 1 && srcsize >= 1)
    {
        if(dest[destsize - 1] > src[srcsize - 1])
        {
            dest[sumsize - 1] = dest[destsize - 1];
            sumsize--;
            destsize--;
        }
        else
        {
            dest[sumsize - 1] = src[srcsize - 1];
            sumsize--;
            srcsize--;
        }
    }


    while(srcsize >= 1)
    {
        dest[sumsize - 1] = src[srcsize - 1];
        sumsize--;
        srcsize--;
    }


    for(auto e: dest)
        cout << e << ' ';
    cout << endl;
    return 0;
}
