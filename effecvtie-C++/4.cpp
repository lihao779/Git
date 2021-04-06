

template<typename T>
class Shared_ptr
{
    public:
        Shared_ptr(const T* ptr = nullptr):ptr_(ptr), pcount_(nullptr)
        {
            if(ptr_)
                pcount_ = new int(1);
        }

        Shared_ptr(const Shared_ptr<T>& s) :ptr_(s.ptr_), pcount_(s.pcount_)
        {
            if(ptr_)
                ++*pcount_;
        }
        Shared_ptr<T>& operator=(const Shared_ptr<T>& s)
        {
            Shared_ptr<T> temp(s);
            if(ptr_ && --*pcount_ == 0)
            {
                delete ptr_;
                delete pcount_;
            }
            ptr_ = s.ptr_;
            pcount_ = s.pcount_;
            ++*pcount_;
            return *this;
        }

        ~Shared_ptr()
        {
            if(ptr_ && --*pcount_ == 0)
            {
                delete ptr_;
                delete pcount_;
            }
        }
    private:
        T* ptr_;
        int* pcount_;
};
