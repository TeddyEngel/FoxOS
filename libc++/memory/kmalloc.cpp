#include <memory>

uint32_t placement_address = 0x0;

uint32_t kmalloc(uint32_t sz)
{
  uint32_t tmp = placement_address;
  placement_address += sz;
  return tmp;
} 
