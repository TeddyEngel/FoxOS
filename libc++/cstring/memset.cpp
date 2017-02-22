#include <cstring>

#include <cstdint>

void* memset(void* dest, uint8_t value, uint32_t size)
{
    uint8_t *temp = (uint8_t *)dest;
    for ( ; size != 0; size--) 
        *temp++ = value;
    return dest;
}
