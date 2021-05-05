#include <stdio.h>
struct ListNode
{
    int val;
    ListNode* next;
};

void Delete(ListNode** phead, ListNode* pToDeleted)
{
    ListNode* cur = *phead;
    ListNode* prev = nullptr;
    if(cur == pToDeleted)
    {
        delete cur;
        *phead = nullptr;
    }
    else
    {
        prev = cur;
        cur = cur->next;
        while(cur->next)
        {
            prev = cur;
            cur = cur->next;
        }
        delete cur;
        prev->next = nullptr;
    }
}
void DeleteNode(ListNode** phead, ListNode* pToDeleted)
{
    ListNode* cur = pToDeleted->next;
    if(cur == NULL)
    {
        //遍历删除
        Delete(phead, pToDeleted);
    }
    else
    {
        pToDeleted->val = cur->val;
        pToDeleted->next = cur->next;
        delete cur;
    }
}
