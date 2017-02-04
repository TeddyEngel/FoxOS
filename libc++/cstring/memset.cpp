#include <cstring>

void* memset(void*, int, size_t)
{
    unsigned char* buf = (unsigned char*) bufptr;
    for (size_t i = 0; i < size; ++i)
        buf[i] = (unsigned char) value;
    return bufptr;
}
