#include <iostream>
#include <vector>
#include <memory>

using namespace std;


int main()
{
    vector<int> vec(10, 3);
    allocator<int> allo;
    auto p = allo.allocate(vec.size() * 2);
    auto q = p;
    for(size_t i = 0; i < vec.size(); i++)
        allo.construct(p++, vec[i]);
    //uninitialized_copy(vec.begin(), vec.end(), p);
    uninitialized_fill_n(p, vec.size(), 20);
    p += 10;
    size_t size = p - q;
    for(size_t i = 0; i < size; i++)
    {
        cout << q[i] << endl;
        allo.destroy(q + i);
    }
    allo.deallocate(q, vec.size() * 2);
    return 0;
}
