#include <cstring>

void* memcpy(void* dstptr, const void* srcptr, std::size_t size)
{
    unsigned char* dst = (unsigned char*) dstptr;
    const unsigned char* src = (const unsigned char*) srcptr;
    for (std::size_t i = 0; i < size; i++)
        dst[i] = src[i];
    return dstptr;
}
