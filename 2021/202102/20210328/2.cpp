#include <stdio.h>
template<class T>
class auto_ptr
{
    public:
        auto_ptr(T* p = nullptr)
            :ptr(p), ower(false)
        { 
            if(ptr)
                ower = true;
        }
        auto_ptr(const auto_ptr<T>& p)
            :ptr(p.ptr), ower(p.ower)
        {
            p.ower = false;
        }
        auto_ptr<T>& operator=(const auto_ptr<T>& p)
        {
            if(this != &p)
            {
                if(ptr && ower)
                    delete ptr;
                ptr = p.ptr;
                ower = p.ower;
                p.ower = false;
            }
            return *this;
        }
        ~auto_ptr() { if(ower && ptr) { delete ptr; ower = false; }; }
    private:
        T* ptr;
        mutable bool ower;
};
namespace bite
{
    template<class T>
    class DFdef
    {
        public:
            void operator()(T* ptr)
            {
                if(ptr)
                    delete ptr;
            }
    };
     
    struct Free
    {
        void operator()(FILE* pf)
        {
            fclose(pf);
        }
    };
    
    template<class T, class DF = DFdef<T>>
    class unique
    {
        public:
            unique(T* p)
                :ptr(p)
            {}
            ~unique();
    
            T& operator*() { return *ptr; }
            T* operator->() { return ptr; }
            unique(const unique<T, DF>&) = delete;
            unique<T, DF>& operator=(const unique<T, DF>&) = delete;
        private:
            T* ptr;
    };
    template<class T, class DF>
    unique<T, DF>::~unique()
    {
        if(ptr)
            DF()(ptr);
    }
}




int main()
{
    return 0;
}
