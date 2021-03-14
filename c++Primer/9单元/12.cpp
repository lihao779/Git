#include <string>
#include <stack>
#include <iostream>

using namespace std;

enum val_type
{
    LP,
    RP,
    VAL,
    ADD,
    SUB
};
struct val
{
    val() = default;
    val(val_type t,double num = 0)
    {
        t_ = t;
        num_ = num;
    }
    
    val_type t_;
    double num_;
};



void Add(stack<val>& s,double num1)
{
   if(s.empty()) 
   {
        cout << "缺少加数" << endl;
        return ;
   }
   else if(s.top().t_ != VAL)
   {
       cout << "缺少加数" << endl;
       return ;
   }
   else
   {
       double num2 = s.top().num_;
       s.pop();
       if(s.top().t_ == LP)
       {
           s.pop();
       }
       s.push(val(VAL,num1+num2));
   }
}
void Sub(stack<val>& s,double num1)
{
   if(s.empty()) 
   {
        cout << "缺少被减数" << endl;
        return ;
   }
   else if(s.top().t_ != VAL)
   {
       cout << "缺少被减数" << endl;
       return ;
   }
   else
   {
       double num2 = s.top().num_;
       s.pop();
       if(s.top().t_ == LP)
       {
           s.pop();
       }
       s.push(val(VAL,num2-num1));
   }

}

int main()
{
    stack<val> stack_;
    string str("(1+1)+((10+1)-2)+(10-2)");
    size_t pos = 0;
    while(pos < str.size())
    {
        if(str[pos] == '(')
        {
            stack_.push(val(LP));
            pos++;
        }
        else if(str[pos] == '+' || str[pos] == '-')
        {
            if(stack_.empty() || stack_.top().t_ != VAL)
            {
                cout << "加号/减号之前需要用算数" << endl;
                return -1;
            }
            else
            {
                if(str[pos] == '+')
                    stack_.push(val(ADD));
                else 
                    stack_.push(val(SUB));
                pos++;
            }
        }
        else if(str[pos] == ')')
        {
            if(stack_.empty())
            {
                cout << "未匹配的右括号" << endl;
                return -1;
            }
            else if(stack_.top().t_ == LP)
            {
                cout << "空括号" << endl;
                return -1;
            }
            else if(stack_.top().t_ == ADD || stack_.top().t_ == SUB)
            {
                cout << "非法右括号" << endl;
                return -1;
            }
            else
            {
                //栈顶存放的是数字
                //提取栈顶元素num1
                //出栈
                //判断栈是否为空
                // 是，未匹配的右括号
                // 否，判断栈顶元素是什么
                //     是左括号
                //        出栈，将num1压栈
                //     是加减号
                //        调用相应的函数
                //     是数字
                //        错误连续数字
                double num1 = stack_.top().num_;
                stack_.pop();
                if(stack_.empty())
                {
                    cout << "未匹配的右括号" << endl;
                    return -1;
                }
                else if(stack_.top().t_ == LP)
                {
                    stack_.pop();
                    stack_.push(val(VAL,num1));
                    pos++;
                }
                else if(stack_.top().t_ == VAL)
                {
                    cout << "错误的连续数字" << endl;
                    return -1;
                }
                else
                {
                    if(stack_.top().t_ == ADD)
                    {
                        //调用ADD
                        stack_.pop();
                        Add(stack_,num1);
                    }
                    else
                    {
                        //调用SUB
                        stack_.pop();
                        Sub(stack_,num1);
                    }
                    pos++;
                }
            }
        }
        else
        {
            //将字符串从pos位置转换为double
            //插入stack_
            //移动pos
            size_t pos_temp = 0;
            double temp = stod(str.substr(pos),&pos_temp);
            stack_.push(val(VAL,temp));
            pos += pos_temp;
        }
    }
    stack<val> temp;
    while(!stack_.empty())
    {
        temp.push(stack_.top());
        if(stack_.top().t_ == ADD)
            cout << "+";
        else if(stack_.top().t_ == SUB)
            cout << "-";
        else 
            cout << stack_.top().num_;
        stack_.pop();
    }
    cout << endl;
    double result = temp.top().num_;
    temp.pop();
    while(!temp.empty())
    {
        if(temp.top().t_ == ADD)
        {
            temp.pop();
            result += temp.top().num_;
            temp.pop();
        }
        else 
        {
            temp.pop();
            result -= temp.top().num_;
            temp.pop();
        }
    }
    cout << result << endl;
    return 0;
}
