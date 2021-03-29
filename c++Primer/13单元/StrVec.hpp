#include <string>
#include <memory>
class StrVec
{
    public:
        StrVec()
            :elements(nullptr), first_free(nullptr), cap(nullptr){}
        StrVec(const StrVec&);
        StrVec(StrVec&&) noexcept;
        StrVec& operator=(const StrVec&);
        StrVec& operator=(StrVec&&) noexcept;
        ~StrVec();

        void push_back(const std::string& s);
        void push_back(std::string&& s);
        size_t size() { return first_free - elements; }
        size_t capacity() { return cap - elements; }
        std::string* begin()const { return elements; }
        std::string* end()const { return first_free; }

    private:
        void chk_n_alloc()
        {
            if(size() == capacity())
                reallocate();
        }
        std::pair<std::string*, std::string*> alloc_n_copy(std::string*, std::string*);
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

std::pair<std::string*, std::string*> StrVec::alloc_n_copy(std::string* b, std::string* e)
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
