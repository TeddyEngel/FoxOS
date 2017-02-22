#include <kernel/MemoryHeap.h>

#include <predicates>

// const uint32_t MemoryHeap::KHEAP_START = 0xC0000000;
// const uint32_t MemoryHeap::KHEAP_INITIAL_SIZE = 0x100000;
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
