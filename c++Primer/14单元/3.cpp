#include <vector>
#include <string>
#include <iostream>
struct Func
{
    int operator()(bool first, int left, int right)
    {
        if(first)
            return left;
        return right;
    }
};

class PrintString
{
    public:
        PrintString(std::ostream& o = std::cout, char ch = ' '): os(o), sep(ch) {}
        void operator()(std::string s)
        {
            os << s << sep;
        }
    private:
        std::ostream& os;
        char sep;
};

class StringCount
{
    public:
        StringCount(size_t n = 10) :vec(n, 0) {}
        void operator()(const std::string& s)
        {
            size_t sz = s.size();
            if(sz <= 10)
                vec[sz]++;
        }
        const std::vector<int>& Get()
        {
            return vec;
        }
    private:
        std::vector<int> vec;
};
int main()
{
    PrintString print;
    std::vector<std::string> vec = {"hello", "world"};
    for(size_t i = 0;i < vec.size(); i++)
        print(vec[i]);
    return 0;
}
