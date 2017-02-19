#ifndef _KERNEL_MEMORY_BLOCK_FOOTER_H
#define _KERNEL_MEMORY_BLOCK_FOOTER_H

#include <cstdint>

#include <kernel/MemoryBlockHeader.h>

class MemoryBlockFooter
{    
public:
    uint32_t _magic;     // Magic number, same as in header_t.
    MemoryBlockHeader* _header; // Pointer to the block header.
};

#endif /* _KERNEL_MEMORY_BLOCK_FOOTER_H */
