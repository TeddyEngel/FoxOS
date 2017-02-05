#include <kernel/idt.h>

#include <cstring>

idt_entry_t idt_manager::entries[256];
idt_ptr_t   idt_manager::ptr;

void idt_manager::initialize()
{
  ptr.limit = sizeof(idt_entry_t) * 256 - 1;
  ptr.base  = (uint32_t)&entries;

  memset(&entries, 0, sizeof(idt_entry_t) * 256);

  // idt_set_gate(0, (uint32_t)isr0 , 0x08, 0x8E);
  // idt_set_gate(1, (uint32_t)isr1 , 0x08, 0x8E);
  // ...
  // idt_set_gate(31, (uint32_t)isr31, 0x08, 0x8E);
  // idt_set_gate(31, (uint32_t)isr32, 0x08, 0x8E);

  idt_flush((uint32_t)&ptr);
}

void idt_manager::set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
  entries[num].base_lo = base & 0xFFFF;
  entries[num].base_hi = (base >> 16) & 0xFFFF;

  entries[num].sel     = sel;
  entries[num].always0 = 0;

  // We must uncomment the OR below when we get to using user-mode.
  // It sets the interrupt gate's privilege level to 3.
  entries[num].flags   = flags /* | 0x60 */;  
}
