#include <vector>

int main()
{
    std::vector<int> v{1,2,3,4,5,6};
    int array[6] = {0};
    for(std::size_t i = 0;i<v.size();i++)
    {
        array[i] = v[i];
    }
    return 0;
}
