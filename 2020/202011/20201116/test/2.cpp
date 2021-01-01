#include<iostream>
#include<list>
using namespace std;

template<class T>
class queue
{
    public:
    queue()
    {}

    void push(const T& date)
    {
        q_.push_back(date);
    }
    void pop()
    {
        q_.pop_front();
    }
    size_t size()const
    {
        return q_.size();
    }
    bool empty()
    {
        return q_.empty();
    }
    T& front()
    {
        return q_.front();
    }
    const T& front()const
    {
        return q_.front();
    }
    T& back()
    {
        return q_.back();
    }
    const T& back()const
    {
        return q_.back();

    }
    private:
        std::list<T> q_;
};

int main()
{
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(5);
    cout<<q.front()<<endl;
    cout<<q.back()<<endl;
    q.pop();
    cout<<q.front()<<endl;
    cout<<q.back()<<endl;
    cout<<q.size()<<endl;

    
    return 0;
}
