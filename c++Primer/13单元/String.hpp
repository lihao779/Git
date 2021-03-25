
#include <memory>
class String
{
    public:
        String()
            :element(nullptr), first_last(nullptr), cap(nullptr){}
        String(const String&);
        String& operator=(const String&);
        ~String();

        size_t size() { return first_last - element; }
        size_t capacity() { return cap - element; }
        void push_back(const char& c);
        char* begin()const { return element; }
        char* end()const { return first_last; }
    private:
        void chk_n_alloc()
        {
            if(size() == capacity())
                reallocate();
        }
        std::pair<char*, char*> alloc_n_copy(char*, char*);
        void free();
        void reallocate();
    
    private:
        std::allocator<char> allo;
        char* element;
        char* first_last;
        char* cap;
};

std::pair<char*, char*> String::alloc_n_copy(char* b, char* e)
{
    auto start = allo.allocate(e - b);
    auto finish = std::uninitialized_copy(b, e, start);
    return {start, finish};
}
    
void String::free()
{
    if(element)
    {
        auto it = first_last;
        while(it != element)
            allo.destroy(--it);
        allo.deallocate(element, cap - element);
    }
}

void String::reallocate()
{
    auto newcapacity = size() ? 2 * size() : 1;
    auto p = allo.allocate(newcapacity);
    auto dest = p;
    auto src = element;
    while(src != first_last)
        allo.construct(dest++, (*src++));
    free();
    first_last = dest;
    element = p;
    cap = p + newcapacity;
}

String::String(const String& s)
{
    auto it = alloc_n_copy(s.begin(), s.end());
    element = it.first;
    first_last = cap = it.second;
    std::cout << "String(const String&)" << std::endl;
}
      
String& String::operator=(const String& s)
{
    if(this != &s)
    {
        auto it = alloc_n_copy(s.begin(), s.end());
        free();
        element = it.first;
        first_last = cap = it.second;
    }
    return *this;
}

String::~String()
{
    free();
}

void String::push_back(const char& c)
{
   chk_n_alloc();
   *first_last++ = c;
}
