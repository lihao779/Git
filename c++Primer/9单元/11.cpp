
#include <queue>
#include <iostream>
#include <string>
#include <deque>
#include <list>
#include <vector>
#include <stack>
#include <forward_list>

using namespace std;

int countone(stack<char>& stk)
{
     int val1 = stk.top();
     stk.pop();
     stk.pop();
     int val2 = stk.top();
     stk.pop();
     return val1+val2;
}

int main()
{
    string s("(1+2)+3+(4+5)+((1+2)+3)");

    stack<char> stk;
    for(auto e: s)
    {
        switch(e)
        {
            case '(':
                stk.push(-2);
                break;
            case ')':
                {
                    int temp = countone(stk);
                    while(!stk.empty() && stk.top() != -2)
                    {
                        stk.push(temp);
                        temp = countone(stk);
                    }
                    if(stk.top() == -2)
                    {
                        stk.pop();
                    }
                    stk.push(temp);
                }
                break;
            case '+':
                {
                    stk.push(-1);
                }
                break;
            default:
                stk.push(e - '0');
                break;
        }
    }
    
    int temp = stk.top();
    stk.pop();
    while(!stk.empty())
    {
        stk.push(temp);
        temp = countone(stk);
    }
    cout << temp;
    return 0;
}
