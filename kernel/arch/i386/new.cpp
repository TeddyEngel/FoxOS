#include <kernel/new.h>

void* operator new(std::size_t sz)
{
    (void)sz;
    return (void *)1;
}
