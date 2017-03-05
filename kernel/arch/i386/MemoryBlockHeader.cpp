#include <kernel/MemoryBlockHeader.h>

int8_t MemoryBlockHeader::less_than(void* a, void* b)
{
   return (((MemoryBlockHeader*)a)->_size < ((MemoryBlockHeader*)b)->_size) ? 1 : 0;
}
