#include <kernel/idt.h>

#include <cstring>

idt_entry_t idt_manager::idt_entries[256];
idt_ptr_t   idt_manager::idt_ptr;

void idt_manager::initialize()
{
  idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
  idt_ptr.base  = (uint32_t)&idt_entries;

  memset(&idt_entries, 0, sizeof(idt_entry_t) * 256);

  // idt_set_gate(0, (uint32_t)isr0 , 0x08, 0x8E);
  // idt_set_gate(1, (uint32_t)isr1 , 0x08, 0x8E);
  // ...
  // idt_set_gate(31, (uint32_t)isr31, 0x08, 0x8E);
  // idt_set_gate(31, (uint32_t)isr32, 0x08, 0x8E);

  idt_flush((uint32_t)&idt_ptr);
}

void idt_manager::set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
  idt_entries[num].base_lo = base & 0xFFFF;
  idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

  idt_entries[num].sel     = sel;
  idt_entries[num].always0 = 0;

  // We must uncomment the OR below when we get to using user-mode.
  // It sets the interrupt gate's privilege level to 3.
  idt_entries[num].flags   = flags /* | 0x60 */;  
}
