#include<deque>

template<class T ,class Con = std::deque<T>>
class stack
{
    public:
        stack()
        {}
        template<class Iterator>
        stack(Iterator first,Iterator last)
        :con_(first,last)
        {}
        void push(const T& date)
        {
            con_.push_back(date);
        }
        void pop()
        {
            if(!empty())
            con_.pop_back();
        }
        bool empty()const
        {
            return con_.empty();
        }
        int size()
        {
            return con_.size();
        }
        T& top()
        {
            return con_.back();
        }
        const T& top()const
        {
            return con_.back();
        }
    private:
        Con con_;

};
