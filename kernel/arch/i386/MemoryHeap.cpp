#include <kernel/MemoryHeap.h>

#include <predicates>

const uint32_t MemoryHeap::KHEAP_START = 0xC0000000;
const uint32_t MemoryHeap::KHEAP_INITIAL_SIZE = 0x100000;
const uint32_t MemoryHeap::KHEAP_LIMIT = 0xFFFFFFFF;
const uint32_t MemoryHeap::INDEX_SIZE = 0x20000;
const uint32_t MemoryHeap::MAGIC = 0x123890AB;
const uint32_t MemoryHeap::MIN_SIZE = 0x70000;

MemoryHeap::MemoryHeap(uint32_t start, uint32_t end, uint32_t max, uint8_t supervisor, uint8_t readOnly)
    : _index(end - start, less_than)
    , _startAddress(start)
    , _endAddress(end)
    , _maxAddress(max)
    , _supervisor(supervisor)
    , _readOnly(readOnly)
{

}

void* MemoryHeap::alloc(uint32_t size, uint8_t pageAlign)
{
    (void)size;
    (void)pageAlign;
    return (void*)0;
}

void MemoryHeap::free(void *p)
{
    (void)p;
}

//TODO: Create aligned / non-aligned version
int32_t MemoryHeap::findSmallestHole(uint32_t size, bool pageAlign)
{
    // Find the smallest hole that will fit.
    uint32_t iterator = 0;
    while (iterator < _index._size)
    {
       MemoryBlockHeader* header = (MemoryBlockHeader*)_index.lookup(iterator);
       // If the user has requested the memory be page-aligned
       if (pageAlign)
       {
           // Page-align the starting point of this header.
           uint32_t location = (uint32_t)header;
           int32_t offset = 0;

           if (((location + sizeof(MemoryBlockHeader)) & 0xFFFFF000) != 0)
               offset = 0x1000 /* page size */  - (location+sizeof(MemoryBlockHeader)) % 0x1000;
           int32_t holeSize = (int32_t)header->_size - offset;
           // Can we fit now?
           if (holeSize >= (int32_t)size)
               break;
       }
       else if (header->_size >= size)
           break;
       ++iterator;
    }
    // Why did the loop exit?
    if (iterator == _index._size)
       return -1; // We got to the end and didn't find anything.
    return iterator;
} 