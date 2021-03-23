#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;
class Test
{
    public:
    Test() = default;
    ~Test() = default;
    string Get()const
    {
        return str_;
    }
    private:
    string str_;
};
size_t hasher(Test& t)
{
    return hash<string>()(t.Get());
}
bool Is_equal(const Test& t1,const Test& t2)
{
    return t1.Get() == t2.Get();
}
int main()
{
    //unordered_map<Test,int> map;关键词Test没有对应的哈希函数
    unordered_map<Test, int, decltype(hasher)*, decltype(Is_equal)*> imap(42, hasher, Is_equal) ; 
    unordered_map<string, int> word_map;
    string word;
    while(cin >> word)
        word_map[word]++;
    return 0;
}
