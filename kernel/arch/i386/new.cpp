#include <kernel/new.h>

void* operator new(std::size_t sz)
{
    return 0;
}
