#include <string>

using namespace std;

class TreeNode
{
    public:
        TreeNode(const string& s = string(), TreeNode* l = nullptr, TreeNode* r = nullptr)
            :value(s)
            ,count(1)
             ,left(l)
             ,right(r)
        {}
    
    private:
        string value;
        int count;
        TreeNode* left;
        TreeNode* right;
};


class BinStrTree
{
    public:
        BinStrTree(TreeNode* r = nullptr)
            :root(r)
        {}
        

    private:
        TreeNode* root;
};
