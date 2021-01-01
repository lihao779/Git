#include<iostream>
#include<vector>
#include<functional>
using namespace std;


template<class T,class Con = vector<T>,class Cmp = less<T>>
class priority_queue
{
    public:
    priority_queue(Cmp cmp = Cmp())
        :cmp_(cmp)
    {}
    template<class Iterator>
    priority_queue(Iterator first,Iterator last,Cmp cmp = Cmp())
        :con_(first,last)
         ,cmp_(cmp)
    {
        int root = (con_.size()-2)/2;
        while(root>=0)
        {
            AdjustDown(root);
            root--;
        }
    }
    void push(const T& date)
    {
        con_.push_back(date);
        AdjustUp();
    }
    void pop()
    {
        if(empty())
            return ;
        swap(con_.front(),con_.back());
        con_.pop_back();
        AdjustDown(0);
    }
    bool empty()
    {
        return con_.empty();
    }

    const T& top()const
    {
        return con_.front();
    }
    size_t size()
    {
        return con_.size();
    }
    

    private:
    void AdjustDown(int parent)
    {
        //小堆
        int child = parent*2+1;
        while(child<con_.size())
        {
            if(child+1<con_.size()&&cmp_(con_[child+1],con_[child]))
            {
                child+=1;
            }
            if(cmp_(con_[child],con_[parent]))
            {
                swap(con_[parent],con_[child]);
            }
            else
            {
                break;
            }
            parent = child;
            child = parent*2+1;
        }
    }
    void AdjustUp()
    {
        int child = con_.size()-1;
        int parent = (child-1)>>1;
        while(parent>=0)
        {
            if(cmp_(con_[child],con_[parent]))
            {
                swap(con_[parent],con_[child]);
                child = parent;
                parent = (child-1)>>1;
            }
            else
                break;
        }
    }
    private:
        Con con_;
        Cmp cmp_;
};


class Greater
{
    public:
        bool operator()(int left,int right)
        {
            return left>right;
        }
};

bool compare(int left,int right)
{
    return left>right;
}
typedef bool (*Cmp)(int left,int right);

int main()
{
    vector<int> v{3,2,5,6,9};
    priority_queue<int,vector<int>,Cmp> q(v.begin(),v.end(),compare);
    cout<<q.top()<<endl;
    q.push(0);
    cout<<q.top()<<endl;

    return 0;
}
