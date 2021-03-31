#include <algorithm>
#include <iostream>
template<class T>
class Vector
{
    public:
    typedef T* iterator;
    Vector():start(nullptr), first_last(nullptr), finish(nullptr){}
    Vector(int, const T&);    
    template<class Iterator>
    Vector(Iterator begin, Iterator end)
    {
        size_t sz = end - begin;
        start = new T[sz];
        first_last = start;
        finish = start + sz;
        while(begin != end)
           *first_last++ = *begin++; 
    }
    Vector(const Vector<T>&);
    Vector(Vector<T>&&);
    ~Vector();
    Vector<T>& operator=(const Vector<T>&);
    Vector<T>& operator=(Vector<T>&&);
    
    
    size_t size()const { return first_last - start; }
    iterator begin()const { return start;}
    iterator end()const { return first_last; }
    void swap(Vector<T>& v)
    {
        std::swap(start, v.start);
        std::swap(first_last, v.first_last);
        std::swap(finish, v.finish);
    }
    bool empty() { return size() == 0; } 
    size_t capacity() { return finish - start; }
    void resize(size_t);
    void reserve(size_t);
    T& operator[](size_t n)
    {
        return start[n];
    }
    const T& operator[](size_t n)const
    {
        return start[n];
    }
    T& front()
    {
        return *start;
    }
    T& back()
    {
        return *(first_last - 1);
    }
    const T& front()const
    {
        return *start;
    }
    const T& back()const
    {
        return *(first_last - 1);
    }
    void assign(size_t n, const T& data)
    {
        Vector<T> v(n, data);
        swap(v);
    }
    template<class Iterator>
    void assign(Iterator begin, Iterator end)
    {
        Vector<T> v(begin, end);
        swap(v);
    }
    void push_back(const T& data)
    {
        if(size() + 1 > capacity())
            AddCapacity(2 * capacity());
        *first_last++ = data;
    }
    void pop_back()
    {
        if(empty())
            return;
        first_last--;
    }
    void insert(iterator pos, const T& data)
    {
        if(size() + 1 > capacity())
            AddCapacity(2 * capacity());
        auto it = end() - 1;
        while(it != pos)
            *(it + 1) = *it--;
        *(pos + 1) = *pos;
        *pos = data;
    }
    template<class InputIterator>
    void insert(iterator pos,InputIterator begin, InputIterator last)
    {
        size_t sz = last - begin;
        if(size() + sz > capacity())
            AddCapacity(size() + sz);
        auto it = end() - 1;
        while(it != pos)
            *(it + sz) = *it--;
        *(pos + sz) = *pos;
        while(begin != last)
            *pos++ = *begin++;
        first_last += sz;
    }
    iterator erase(iterator pos)
    {
        if(empty())
            return end();
        while(pos != first_last - 1)
            *pos++ = *(pos + 1);
        first_last--;
        return pos;
    }
    iterator erase(iterator begin, iterator last)
    {
        if(empty())
            return end();
        size_t sz = last - begin;
        while(last != first_last)
            *(last - sz) = *last++;
        first_last -= sz;
        return begin;
    }
    void clear()
    {
        first_last = start;
    }





    private:
    void Release()
    {
        if(start)
        {
            delete start;
            start = nullptr;
            first_last = nullptr;
            finish = nullptr;
        }
    }
    void AddCapacity(size_t n)
    {
        T* temp = new T[n];
        size_t sz = size();
        for(size_t i = 0; i < sz; i++)
            temp[i] = start[i];
        for(size_t i = sz; i < n; i++)
        {
            temp[i] = T();
        }
        Release();
        start = temp;
        first_last = start + sz;
        finish = start + n;
    }
    private:
        T* start;
        T* first_last;
        T* finish;
};
template<class T>
inline Vector<T>::Vector(int n, const T& data)
    :start(new T[n]), first_last(start), finish(start + n)
{
   while(first_last != finish)
       *first_last++ = data;
}
template<class T>
inline Vector<T>::Vector(const Vector<T>& v)
{
   size_t sz = v.size();
   start = new T[sz];
   first_last = start;
   finish = start + sz;
   auto it = v.begin();
   while(it != v.end())
       *first_last++ = *it++;
}
template<class T>
inline Vector<T>::Vector(Vector<T>&& v)
{
    start = v.start;
    first_last = v.first_last;
    finish = v.finish;
    v.start = nullptr;
    v.first_last = nullptr;
    v.finish = nullptr;
}
template<class T>
inline Vector<T>::~Vector()
{
    Release();
}
template<class T>
inline Vector<T>& Vector<T>::operator=(const Vector<T>& v)
{
    if(&v != this)
    {
        Vector<T> temp(v);
        swap(temp);
    }
    return *this;
}
template<class T>
Vector<T>& Vector<T>::operator=(Vector<T>&& v)
{
    if(&v != this)
    {
        Release();
        start = v.start;
        first_last = v.first_last;
        finish = v.finish;
    }
    return *this;
}
template<class T>
inline void Vector<T>::resize(size_t n)
{
    if(n > size())
        AddCapacity(n);
    first_last = start + n;
}
template<class T>
inline void Vector<T>::reserve(size_t n)
{
    if(n > size())
        AddCapacity(n);
}
