#ifndef _KERNEL_MEMORY_HEAP_H
#define _KERNEL_MEMORY_HEAP_H

#include <cstddef>
#include <cstdint>
#include <ordered_array>

#include <kernel/MemoryBlockHeader.h>
#include <kernel/MemoryBlockFooter.h>

class MemoryHeap
{
public:
  static const uint32_t KHEAP_START;
  static const uint32_t KHEAP_INITIAL_SIZE;
  static const uint32_t KHEAP_LIMIT;
  static const uint32_t INDEX_SIZE;
  static const uint32_t MAGIC;
  static const uint32_t MIN_SIZE;

public:
  MemoryHeap(uint32_t start, uint32_t end, uint32_t max, uint8_t supervisor, uint8_t readOnly);

  static void* operator new(std::size_t size);
  // Create a new heap
  // heap_t *create_heap(uint32_t start, uint32_t end, uint32_t max, uint8_t supervisor, uint8_t readonly);

  // To call until normal construction works
  //static bool place(MemoryHeap*, uint32_t start, uint32_t end, uint32_t max, uint8_t supervisor, uint8_t readOnly);

  // Allocates a contiguous region of memory 'size' in size. If page_align==1, it creates that block starting on a page boundary.
  void *alloc(uint32_t size, uint8_t pageAlign);

  // Releases a block allocated with 'alloc'.
  void free(void *p);

  int32_t findSmallestHole(uint32_t size, bool pageAlign);

public:
  ordered_array _index;
  uint32_t _startAddress; // The start of our allocated space.
  uint32_t _endAddress;   // The end of our allocated space. May be expanded up to max_address.
  uint32_t _maxAddress;   // The maximum address the heap can be expanded to.
  uint8_t _supervisor;     // Should extra pages requested by us be mapped as supervisor-only?
  uint8_t _readOnly;       // Should extra pages requested by us be mapped as read-only?
};

#endif /* _KERNEL_MEMORY_HEAP_H */