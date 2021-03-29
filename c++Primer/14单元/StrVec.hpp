#include <string>
#include <memory>
class StrVec
{
    friend bool operator==(const StrVec& s1, const StrVec& s2);
    friend bool operator!=(const StrVec& s1, const StrVec& s2);
    friend bool operator<(const StrVec& s1, const StrVec& s2);
    friend bool operator>(const StrVec& s1, const StrVec& s2);
    public:
        StrVec()
            :elements(nullptr), first_free(nullptr), cap(nullptr){}
        StrVec(const StrVec&);
        StrVec(StrVec&&) noexcept;
        StrVec& operator=(const StrVec&);
        StrVec& operator=(StrVec&&) noexcept;
        StrVec& operator=(std::initializer_list<std::string> li);
        std::string& operator[](size_t sz);
        const std::string& operator[](size_t sz)const;
        ~StrVec();

        void push_back(const std::string& s);
        void push_back(std::string&& s);
        size_t size()const { return first_free - elements; }
        size_t capacity() { return cap - elements; }
        std::string* begin()const { return elements; }
        std::string* end()const { return first_free; }
        std::string* begin() { return elements; }
        std::string* end() { return first_free; }

    private:
        void chk_n_alloc()
        {
            if(size() == capacity())
                reallocate();
        }
        std::pair<std::string*, std::string*> alloc_n_copy(const std::string*, const std::string*);
        void free();
        void reallocate();
    private:
        static std::allocator<std::string> allo; //分配未初始化的string空间
        std::string* elements; //vec的begin位置
        std::string* first_free; //vec的end位置
        std::string* cap; //vec最后有一个开辟空间的下一个位置
};

StrVec::StrVec(const StrVec& s)
{
    auto it = alloc_n_copy(s.begin(), s.end());
    first_free = it.second;
    elements = it.first;
    cap = it.second;
}

StrVec::StrVec(StrVec&& s) noexcept
    :elements(s.elements), first_free(s.first_free), cap(s.cap)
{
    s.first_free = s.elements = s.cap = nullptr;
}
StrVec& StrVec::operator=(const StrVec& s)
{
    if(&s != this)
    {
        free();
        auto it = alloc_n_copy(s.begin(), s.end());
        first_free = it.second;
        elements = it.first;
        cap = it.second;
    }
    return *this;
}

StrVec& StrVec::operator=(StrVec&& s) noexcept
{
    if(this != &s)
    {
        free();
        elements = s.elements;
        first_free = s.first_free;
        cap = s.cap;
        s.elements = s.first_free = s.cap = nullptr;
    }
    return *this;
}
StrVec& StrVec::operator=(std::initializer_list<std::string> li)
{
   auto it = alloc_n_copy(li.begin(), li.end());
   free();
   elements = it.first;
   cap = first_free = it.second;
   return *this;
}

std::string& StrVec::operator[](size_t sz) 
{
    return elements[sz];
}

const std::string& StrVec::operator[](size_t sz)const 
{
    return elements[sz];
}

StrVec::~StrVec()
{
    free();
}

void StrVec::push_back(const std::string& s)
{
    chk_n_alloc();
    allo.construct(first_free++, s);
}
void StrVec::push_back(std::string&& s)
{
    chk_n_alloc();
    allo.construct(first_free++, std::move(s));
}

std::pair<std::string*, std::string*> StrVec::alloc_n_copy(const std::string* b, const std::string* e)
{
    auto data = allo.allocate(e - b);
    auto q = std::uninitialized_copy(b, e, data);
    return {data, q};
}

void StrVec::free()
{
    if(elements)
    {
        for(auto i = first_free; i != elements;)
            allo.destroy(--i);
        allo.deallocate(elements, cap - elements);
    }
}

void StrVec::reallocate()
{
    size_t newcapacity = size() ? 2*size() : 1;
    auto p = allo.allocate(newcapacity);
    auto dest = p;
    auto scr = elements;
    while(scr != first_free)
        allo.construct(dest++, std::move(*scr++));
    free();
    elements = p;
    first_free = dest;
    cap = p + newcapacity;
}

bool operator==(const StrVec& s1, const StrVec& s2)
{
    if(s1.size() != s2.size())
        return false;
    auto it1 = s1.begin();
    auto it2 = s2.begin();
    while(it1 != s1.end())
    {
        if(*it1 != *it2)
            return false;
    }
    return true;
}

bool operator!=(const StrVec& s1, const StrVec& s2)
{
    return !(s1 == s2);
}

bool operator<(const StrVec& s1, const StrVec& s2)
{
    size_t minsize = (s1.size() > s2.size())? s2.size(): s1.size();
    for(size_t i = 0; i < minsize; i++)
    {
        if(s1.elements[i] > s2.elements[i])
            return false;
        else if(s1.elements[i] < s2.elements[i])
            return true;
    }
    if(s1.size() >= s2.size())
        return false;
    return true;
}

bool operator>(const StrVec& s1, const StrVec& s2)
{
    if(s1 == s2)
        return false;
    if(s1 < s2)
        return false;
    return true;
}
