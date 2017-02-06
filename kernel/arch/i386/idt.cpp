#include <kernel/idt.h>

#include <cstdio>
#include <cstring>

#include <kernel/isr.h>
#include <kernel/irq.h>

idt_entry_t idt_manager::entries[IDT_ENTRIES];
idt_ptr_t   idt_manager::ptr;

void idt_manager::initialize()
{
  ptr.limit = sizeof(idt_entry_t) * IDT_ENTRIES - 1;
  ptr.base  = (uint32_t)&entries;

  memset(&entries, 0, sizeof(idt_entry_t) * IDT_ENTRIES);

  remap_irqs(PIC_MASTER, PIC_MASTER + PIC_MASTER_IRQ_ENTRIES);

  set_cpu_gates();

  set_irq_gates();

  idt_flush((uint32_t)&ptr);
}

void idt_manager::enable_interrupts()
{
  asm volatile ("sti");
}

void idt_manager::disable_interrupts()
{
  asm volatile ("cli");
}

bool idt_manager::are_interrupts_enabled()
{
  unsigned long flags;
  asm volatile ( "pushf\n\t"
                 "pop %0"
                 : "=g"(flags) );
  return flags & (1 << 9);
}

/*
arguments:
  offset1 - vector offset for master PIC
    vectors on the master become offset1..offset1+7
  offset2 - same for slave PIC: offset2..offset2+7
*/
void idt_manager::remap_irqs(int offset1, int offset2)
{
  uint8_t a1, a2;
 
  a1 = inb(PIC_MASTER_DATA);                        // save masks
  a2 = inb(PIC_SLAVE_DATA);
 
  outb(PIC_MASTER_COMMAND, ICW1_INIT+ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
  io_wait();
  outb(PIC_SLAVE_COMMAND, ICW1_INIT+ICW1_ICW4);
  io_wait();
  outb(PIC_MASTER_DATA, offset1);                 // ICW2: Master PIC vector offset
  io_wait();
  outb(PIC_SLAVE_DATA, offset2);                 // ICW2: Slave PIC vector offset
  io_wait();
  outb(PIC_MASTER_DATA, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
  io_wait();
  outb(PIC_SLAVE_DATA, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)
  io_wait();
 
  outb(PIC_MASTER_DATA, ICW4_8086);
  io_wait();
  outb(PIC_SLAVE_DATA, ICW4_8086);
  io_wait();
 
  outb(PIC_MASTER_DATA, a1);   // restore saved masks.
  outb(PIC_SLAVE_DATA, a2);
}

void idt_manager::set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
  entries[num].base_lo = base & 0xFFFF;
  entries[num].base_hi = (base >> 16) & 0xFFFF;

  entries[num].sel     = sel;
  entries[num].always0 = 0;

  entries[num].flags   = flags;
}

void idt_manager::set_cpu_gates()
{
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
}

void idt_manager::set_irq_gates()
{
  set_gate(32, (uint32_t)irq0, 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(33, (uint32_t)irq1, 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(34, (uint32_t)irq2, 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(35, (uint32_t)irq3, 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(36, (uint32_t)irq4, 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(37, (uint32_t)irq5, 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(38, (uint32_t)irq6, 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(39, (uint32_t)irq7, 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(40, (uint32_t)irq8, 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(41, (uint32_t)irq9, 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(42, (uint32_t)irq10, 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(43, (uint32_t)irq11, 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(44, (uint32_t)irq12, 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(45, (uint32_t)irq13, 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(46, (uint32_t)irq14, 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  set_gate(47, (uint32_t)irq15, 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
}
