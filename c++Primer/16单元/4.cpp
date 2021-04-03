#include <vector>
#include <memory>
template<class T>
class Blob
{
    public:
        typedef T value_type;
        typedef typename std::vector<T>::size_type size_type;
    public:
        Blob() = default;
        Blob(const Blob& b)
            :data(b.data)
        {}
        Blob(std::initializer_list<T> li)
            :data(std::make_shared<std::vector<T>>(li))
        {}
        size_type size()const 
        {
            return data->size();
        }
        bool empty()const 
        {
            return data->empty();
        }
        void push_back(const T& x)
        {
            data->push_back(x);
        }
        void push_back(T&& x)
        {
            data->push_back(std::move(x));
        }
        void pop_back()
        {
            if(!empty())
                data->pop_back();
        }
        T& back()
        {
            if(!empty())
                return data->back();
        }
        T& operator[](size_t index)
        {
            return (*data)[index];
        }


    private:
        std::shared_ptr<std::vector<T>> data;
    
};
