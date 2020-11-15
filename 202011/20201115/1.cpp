#include<iostream>
#include<vector>

namespace bite
{
    template<class T>
    class stack
    {
        public:
            stack()
            {}
            void size()const
            {
                return v_.size();
            }
            void push(const T& date)
            {
                v_.push_back(date);
            }
            void pop()
            {
                v_.pop_back();
            }
            bool empty()const
            {
                return v_.empty();
            }
            T& top()
            {
                return v_.back();
            }
            const T& top()const
            {
                return v_.back();
            }
        private:
            std::vector<T> v_;
    };
}
