#include <malloc.h>
#include <iostream>


void* operator new(size_t sz)
{
    if(void* mem = malloc(sz))
        return mem;
    else
        throw std::bad_alloc();
}
void operator delete(void* mem)noexcept
{
    free(mem);
}
