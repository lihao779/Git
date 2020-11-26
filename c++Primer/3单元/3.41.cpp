#include <vector>

int main()
{
    int array[] = {1,2,3,4,5,6};
    std::vector<int> v(array,array+sizeof(array)/sizeof(0));
    return 0;
}
