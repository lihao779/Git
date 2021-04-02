#include <iostream>


template<class T>
class SmartPtr
{
    public:
        SmartPtr(T* ptr = nullptr)
            :ptr_(ptr)
        {}
        ~SmartPtr()
        {
            if(ptr_)
                delete ptr_;
        }

        T& operator*()
        {
            return *ptr_;
        }
        T* operator->()
        {
            return ptr_;
        }

    private:
        T* ptr_;
};
template<class T>
class auto_ptr
{
    public:
        auto_ptr(T* p = nullptr)
            :ptr(p)
        {}
        
        auto_ptr(auto_ptr<T>& p)
            :ptr(p.ptr)
        {
            p.ptr = nullptr;
        }
        
        auto_ptr<T>& operator=(auto_ptr<T>& p)
        {
            if(this != &p)
            {
                if(ptr)
                    delete ptr;
                ptr = p.ptr;
                p.ptr = nullptr;
            }
            return *this;
        }

        ~auto_ptr()
        {
            if(ptr)
            {
                delete ptr;
            }
        }

        T& operator*() { return *ptr; }
        T* operator->() { return ptr; }
    private:
        T* ptr;
};
int main()
{
    //SmartPtr<int> s = new int(1);
    //cout << *s << endl;
    auto_ptr<int> p1(new int(1));
    auto_ptr<int> p2 = p1;
    //std::cout << *p1 << std::endl;
    std::cout << *p2 << std::endl;
    return 0;
}
