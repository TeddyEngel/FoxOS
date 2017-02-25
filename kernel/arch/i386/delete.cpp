#include <kernel/delete.h>

void operator delete(void* ptr)
{
    (void)ptr;
}
