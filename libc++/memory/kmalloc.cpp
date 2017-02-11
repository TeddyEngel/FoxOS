#include <memory>

uint32_t placement_address = 0x0;

uint32_t kmalloc_int(uint32_t sz, bool align, uint32_t* physicalAddress)
{
    if (align == true && (placement_address & 0xFFFFF000)) // If the address is not already page-aligned
    {
        // Align it.
        placement_address &= 0xFFFFF000;
        placement_address += 0x1000;
    }
    if (phys)
        *phys = placement_address;
    uint32_t tmp = placement_address;
    placement_address += sz;
    return tmp;
} 

uint32_t kmalloc_a(uint32_t sz)
{
    kmalloc_int(sz, true, 0);
}

uint32_t kmalloc_p(uint32_t sz, uint32_t *phys)
{
    kmalloc_int(sz, false, phys);
}

uint32_t kmalloc_ap(uint32_t sz, uint32_t *phys)
{
    kmalloc_int(sz, true, phys);
}

uint32_t kmalloc(uint32_t sz)
{
    kmalloc_int(sz, false, 0);
}
