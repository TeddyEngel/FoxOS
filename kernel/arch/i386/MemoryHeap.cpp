#include <kernel/MemoryHeap.h>

#include <cstdio>
#include <cstdint>
#include <memory>
#include <predicates>

#include <kernel/MemoryBlockHeader.h>
#include <kernel/PageTypes.h>

const uint32_t MemoryHeap::KHEAP_START = 0xC0000000;
const uint32_t MemoryHeap::KHEAP_INITIAL_SIZE = 0x100000;
const uint32_t MemoryHeap::KHEAP_LIMIT = 0xFFFFFFFF;
const uint32_t MemoryHeap::INDEX_SIZE = 0x20000;
const uint32_t MemoryHeap::MAGIC = 0x123890AB;
const uint32_t MemoryHeap::MIN_SIZE = 0x70000;

MemoryHeap::MemoryHeap(uint32_t start, uint32_t end, uint32_t max, uint8_t supervisor, uint8_t readOnly)
    : _index((void*)start, INDEX_SIZE, &MemoryBlockHeader::less_than)
    , _startAddress(start)
    , _endAddress(end)
    , _maxAddress(max)
    , _supervisor(supervisor)
    , _readOnly(readOnly)
{
    // TODO: Find a way to stop construction if those are true, maybe throwing exception or something
    // All our assumptions are made on startAddress and endAddress being page-aligned.
    // if (start % PAGE_SIZE != 0)
    //     return false;
    // if (end % PAGE_SIZE != 0)
    //     return false;

    // Shift the start address forward to resemble where we can start putting data.
   _startAddress += sizeof(type_t) * INDEX_SIZE;

   // Make sure the start address is page-aligned.
   if (_startAddress & 0xFFFFF000 != 0)
   {
       _startAddress &= 0xFFFFF000;
       _startAddress += PAGE_SIZE;
   }

   // printf("memory heap address: %d\n", this);
   // printf("ordered_array address: %d\n", &this->_index);
   // printf("ordered_array size: %d\n", this->_index._size);
   // printf("ordered_array size address: %d\n", &this->_index._size);

   // We start off with one large hole in the index.
   MemoryBlockHeader* hole = (MemoryBlockHeader*)_startAddress;
   hole->_size = _endAddress - _startAddress;
   hole->_magic = MAGIC;
   hole->_isHole = 1;
   _index.insert((type_t)hole);
   // printf("ordered_array size: %d\n", this->_index._size);
}

void* MemoryHeap::operator new(std::size_t size)
{
    // MemoryHeap* memoryHeap = (MemoryHeap*)kmalloc(size);
    
    // printf("allocating a memory heap of size %d!\n", (int)size);

    return (void*)kmalloc(size);
}

/*
bool MemoryHeap::place(MemoryHeap* memoryHeap, uint32_t start, uint32_t end, uint32_t max, uint8_t supervisor, uint8_t readOnly)
{
    if (memoryHeap == nullptr)
        return false;
    // All our assumptions are made on startAddress and endAddress being page-aligned.
    if (start % PAGE_SIZE != 0)
        return false;
    if (end % PAGE_SIZE != 0)
        return false;

   // Initialise the index.
   memoryHeap->_index = ordered_array((void*)start, INDEX_SIZE, &MemoryBlockHeader::less_than);
   printf("memory heap address: %d\n", memoryHeap);
   printf("ordered_array address: %d\n", &memoryHeap->_index);
   printf("ordered_array size: %d\n", memoryHeap->_index._size);
   printf("ordered_array size address: %d\n", &memoryHeap->_index._size);

   // Shift the start address forward to resemble where we can start putting data.
   start += sizeof(type_t) * INDEX_SIZE;

   // Make sure the start address is page-aligned.
   if (start & 0xFFFFF000 != 0)
   {
       start &= 0xFFFFF000;
       start += PAGE_SIZE;
   }

   // Write the start, end and max addresses into the heap structure.
   memoryHeap->_startAddress = start;
   memoryHeap->_endAddress = end;
   memoryHeap->_maxAddress = max;
   memoryHeap->_supervisor = supervisor;
   memoryHeap->_readOnly = readOnly;

   // We start off with one large hole in the index.
   MemoryBlockHeader* hole = (MemoryBlockHeader*)start;
   hole->_size = end - start;
   hole->_magic = MAGIC;
   hole->_isHole = 1;
   memoryHeap->_index.insert((type_t)hole);
   return true;
}
*/

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
               offset = PAGE_SIZE - (location+sizeof(MemoryBlockHeader)) % PAGE_SIZE;
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