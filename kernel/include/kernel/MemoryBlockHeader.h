#ifndef _KERNEL_MEMORY_BLOCK_HEADER_H
#define _KERNEL_MEMORY_BLOCK_HEADER_H

#include <cstdint>

class MemoryBlockHeader
{    
public:
  uint32_t _magic;  // Magic number, used for error checking and identification.
  uint8_t _isHole; // 1 if this is a hole, 0 if this is a block.
  uint32_t _size;   // Size of the block, including this and the footer.
};

#endif /* _KERNEL_MEMORY_BLOCK_HEADER_H */
