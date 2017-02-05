#include <kernel/idt.h>

#include <cstring>

idt_entry_t idt_manager::entries[IDT_ENTRIES];
idt_ptr_t   idt_manager::ptr;

void idt_manager::initialize()
{
  ptr.limit = sizeof(idt_entry_t) * IDT_ENTRIES - 1;
  ptr.base  = (uint32_t)&entries;

  memset(&entries, 0, sizeof(idt_entry_t) * IDT_ENTRIES);

  set_gate(0, (uint32_t)isr0 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(1, (uint32_t)isr1 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(2, (uint32_t)isr2 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(3, (uint32_t)isr3 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(4, (uint32_t)isr4 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(5, (uint32_t)isr5 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(6, (uint32_t)isr6 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(7, (uint32_t)isr7 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(8, (uint32_t)isr8 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(9, (uint32_t)isr9 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(10, (uint32_t)isr10 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(11, (uint32_t)isr11 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(12, (uint32_t)isr12 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(13, (uint32_t)isr13 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(14, (uint32_t)isr14 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(15, (uint32_t)isr15 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(16, (uint32_t)isr16 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(17, (uint32_t)isr17 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(18, (uint32_t)isr18 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(19, (uint32_t)isr19 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(20, (uint32_t)isr20 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(21, (uint32_t)isr21 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(22, (uint32_t)isr22 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(23, (uint32_t)isr23 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(24, (uint32_t)isr24 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(25, (uint32_t)isr25 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(26, (uint32_t)isr26 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(27, (uint32_t)isr27 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(28, (uint32_t)isr28 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(29, (uint32_t)isr29 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(30, (uint32_t)isr30 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(31, (uint32_t)isr31 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);

  idt_flush((uint32_t)&ptr);
}

void idt_manager::set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
  if (num < 0)
    return;
  if (num > IDT_ENTRIES)
    return;
  entries[num].base_lo = base & 0xFFFF;
  entries[num].base_hi = (base >> 16) & 0xFFFF;

  entries[num].sel     = sel;
  entries[num].always0 = 0;

  entries[num].flags   = flags;
}
