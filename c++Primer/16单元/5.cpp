#include <algorithm>
#include <set>

bool Isbig(int left, int right)
{
    return left > right;
}

struct ISBIG
{
    bool operator()(const int left, const int right)
    {
        return left > right;
    }
};

int main()
{
    std::set<int, decltype(Isbig)*> myset1(Isbig);
    ISBIG i = ISBIG();
    std::set<int, ISBIG> myset2(i);
    auto f = [](int left, int right){ return left > right; };
    std::set<int, decltype(f)> myset3(f);
    return 0;
}
