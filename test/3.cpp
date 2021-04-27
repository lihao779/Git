#include <iostream>
#include <memory>

using namespace std;
#if 0
struct ListNode
{
    ListNode(int x):prev(nullptr), next(nullptr), data(x)
    {
        cout << "ListNode(int x)" << endl;
    }

    ~ListNode()
    {
        cout << "~ListNode()" << endl;
    }
    shared_ptr<ListNode> prev;
    shared_ptr<ListNode> next;
    int data;
};
#endif
struct ListNode
{
    ListNode(int x): data(x)
    {
        cout << "ListNode(int x)" << endl;
    }

    ~ListNode()
    {
        cout << "~ListNode()" << endl;
    }
    weak_ptr<ListNode> prev;
    weak_ptr<ListNode> next;
    int data;
};



int main()
{
    shared_ptr<ListNode> sp1(new ListNode(1));
    shared_ptr<ListNode> sp2( new ListNode(2));
    sp1->next = sp2;
    sp2->prev = sp1;
    return 0;
}
