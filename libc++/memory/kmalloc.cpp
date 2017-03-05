#include <memory>

#include <cstddef>

#include <kernel/PageTypes.h>

extern uint32_t end;
uint32_t placement_address = (uint32_t)&end;

uint32_t kmalloc_int(uint32_t sz, bool align, uint32_t* physicalAddress)
{
    if (align == true && (placement_address & 0xFFFFF000)) // If the address is not already page-aligned
    {
        // Align it.
        placement_address &= 0xFFFFF000;
        placement_address += PAGE_SIZE;
    }
    if (physicalAddress)
        *physicalAddress = placement_address;
    uint32_t tmp = placement_address;
    placement_address += sz;
    return tmp;
} 

uint32_t kmalloc_a(uint32_t sz)
{
    kmalloc_int(sz, true, 0);
}

uint32_t kmalloc_p(uint32_t sz, uint32_t* physicalAddress)
{
    kmalloc_int(sz, false, physicalAddress);
}

uint32_t kmalloc_ap(uint32_t sz, uint32_t* physicalAddress)
{
    kmalloc_int(sz, true, physicalAddress);
}

uint32_t kmalloc(uint32_t sz)
{
    kmalloc_int(sz, false, 0);
}
