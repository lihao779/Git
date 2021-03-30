#include <cstring>
#include <iostream>
class String
{
    public:
        String(): ptr_(nullptr), size_(0), capacity_(0) {}
        String(const String&);
        String(const String&, size_t, size_t);
        String(const char*);
        String(const char*, size_t);
        String(size_t, char);
        String(String&&);
        template<class Iterator>
        String(Iterator, Iterator);

        ~String() 
        {
            if(ptr_)
            {
                delete ptr_;
                size_ = 0;
                capacity_ = 0;
            }
        }
        
        String& operator=(const String&);
        String& operator=(String&&);

        size_t size()const { return size_; }
        size_t capacity()const { return capacity_; }
        bool empty() { return size() == 0; }
        void resize(size_t n);
        void reserve(size_t n);
        void clear();

        char& operator[](size_t n);
        const char& operator[](size_t n)const;

        String& operator+=(const String&);
        String& operator+=(const char*);
        String& operator+=(char ch);

        String& append(const String&);
        void push_back(char ch);
        String& assign(size_t, char ch);
        String& insert(char);
        String& replace(size_t, size_t, const String&);
        char* c_str()const { return ptr_; }

        void swap(String&);
    private:
        void upcapacity()
        {
            char* temp = new char[capacity_ * 2];
            strcpy(temp, ptr_);
            delete ptr_;
            ptr_ = temp;
            capacity_ *= 2; 
            for(size_t i = size_; i < capacity_; i++)
            {
                *(ptr_ + i) = '\0';
            }
        }
    private:
        char* ptr_;
        size_t size_;
        size_t capacity_;
};

String::String(const String& s)
{
    ptr_ = new char[s.size() + 1];
    strcpy(ptr_, s.c_str());
    size_ = s.size();
    capacity_ = s.size();
}
String::String(const String& s, size_t pos, size_t n)
{
    size_t sz = s.size();
    if(pos + n > sz) 
        n = sz - pos;
    ptr_ = new char[n + 1];
    strncpy(ptr_, s.c_str() + pos, n);
    *(ptr_ + n) = '\0'; 
    size_ = n;
    capacity_ = n;

}
String::String(const char* s)
{
    size_t sz = strlen(s);
    ptr_ = new char[sz + 1];
    strcpy(ptr_, s);
    size_ = sz;
    capacity_ = sz;
}
String::String(const char* s, size_t n)
{
    size_t sz = strlen(s);
    if(n > sz)
        n = sz;
    ptr_ = new char[n + 1];
    strncpy(ptr_, s, n);
    *(ptr_ + n) = '\0';
    size_ = sz;
    capacity_ = sz;
}
String::String(size_t n, char ch)
{
    ptr_ = new char[n + 1];
    memset(ptr_, n, ch);
    *(ptr_ + n) = '\0';
    size_ = n;
    capacity_ = n;
}
String::String(String&& s)
{
    ptr_ = s.ptr_;
    size_ = s.size();
    capacity_ = s.capacity();
    s.ptr_ = nullptr;
    s.size_ = 0;
    s.capacity_ = 0;
}
template<class Iterator>
String::String(Iterator begin, Iterator end)
{
    while(begin != end)
    {
        push_back(*begin);
        ++begin;
    }
}
String& String::operator=(const String& s)
{   
    if(&s != this)
    {
        char* temp = new char[s.size() + 1];
        delete ptr_;
        ptr_ = temp;
        size_ = s.size();
        capacity_ = s.capacity();
    }
    return *this;
}
String& String::operator=(String&& s)
{
    if(&s != this)
    {
        delete ptr_;
        ptr_ = s.ptr_;
        size_ = s.size();
        capacity_ = s.capacity();
        s.capacity_ = 0;
        s.size_ = 0;
    }
    return *this;
}
void String::resize(size_t n)
{
    if(n > capacity())
        upcapacity();
    size_ = n;
}
void String::reserve(size_t n)
{
    if(n > capacity())
        upcapacity();
}
void String::clear()
{
    size_ = 0;
}
