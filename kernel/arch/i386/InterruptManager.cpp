#include <kernel/InterruptManager.h>

#include <cstdio>
#include <cstring>

#include <kernel/pic.h>
#include <kernel/irq_handlers.h>

InterruptManager::InterruptManager()
{
  for (int i = 0; i < IDT_ENTRIES; ++i)
    handlers[i] = 0;
}

void InterruptManager::initialize()
{
  ptr.limit = sizeof(idt_entry_t) * IDT_ENTRIES - 1;
  ptr.base  = (uint32_t)&entries;

  memset(&entries, 0, sizeof(idt_entry_t) * IDT_ENTRIES);

  remapIrqs(PIC_MASTER, PIC_MASTER + PIC_MASTER_IRQ_ENTRIES);

  setCpuGates();

  setIrqGates();

  idt_flush((uint32_t)&ptr);
}

void InterruptManager::enableInterrupts()
{
  asm volatile("sti");
}

void InterruptManager::disableInterrupts()
{
  asm volatile("cli");
}

bool InterruptManager::areInterruptsEnabled()
{
  unsigned long flags;
  asm volatile( "pushf\n\t"
                 "pop %0"
                 : "=g"(flags) );
  return flags & (1 << 9);
}

bool InterruptManager::hasHandler(uint8_t n)
{
    return handlers[n] != 0;
}

fct_handler InterruptManager::getHandler(uint8_t n)
{
    return handlers[n];
}

void InterruptManager::registerHandler(uint8_t n, fct_handler handler)
{
    handlers[n] = handler;
}

/*
arguments:
  offset1 - vector offset for master PIC
    vectors on the master become offset1..offset1+7
  offset2 - same for slave PIC: offset2..offset2+7
*/
void InterruptManager::remapIrqs(int32_t offset1, int32_t offset2)
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

void InterruptManager::setGate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
  entries[num].base_lo = base & 0xFFFF;
  entries[num].base_hi = (base >> 16) & 0xFFFF;

  entries[num].sel     = sel;
  entries[num].always0 = 0;

  entries[num].flags   = flags;
}

void InterruptManager::setCpuGates()
{
  setGate(0, (uint32_t)isr0 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(1, (uint32_t)isr1 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(2, (uint32_t)isr2 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(3, (uint32_t)isr3 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(4, (uint32_t)isr4 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(5, (uint32_t)isr5 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(6, (uint32_t)isr6 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(7, (uint32_t)isr7 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(8, (uint32_t)isr8 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(9, (uint32_t)isr9 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(10, (uint32_t)isr10 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(11, (uint32_t)isr11 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(12, (uint32_t)isr12 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(13, (uint32_t)isr13 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(14, (uint32_t)isr14 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(15, (uint32_t)isr15 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(16, (uint32_t)isr16 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(17, (uint32_t)isr17 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(18, (uint32_t)isr18 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(19, (uint32_t)isr19 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(20, (uint32_t)isr20 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(21, (uint32_t)isr21 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(22, (uint32_t)isr22 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(23, (uint32_t)isr23 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(24, (uint32_t)isr24 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(25, (uint32_t)isr25 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(26, (uint32_t)isr26 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(27, (uint32_t)isr27 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(28, (uint32_t)isr28 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(29, (uint32_t)isr29 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(30, (uint32_t)isr30 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(31, (uint32_t)isr31 , 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
}

void InterruptManager::setIrqGates()
{
  setGate(32, (uint32_t)irq0, 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(33, (uint32_t)irq1, 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(34, (uint32_t)irq2, 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(35, (uint32_t)irq3, 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(36, (uint32_t)irq4, 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(37, (uint32_t)irq5, 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(38, (uint32_t)irq6, 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(39, (uint32_t)irq7, 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(40, (uint32_t)irq8, 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(41, (uint32_t)irq9, 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(42, (uint32_t)irq10, 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(43, (uint32_t)irq11, 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(44, (uint32_t)irq12, 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(45, (uint32_t)irq13, 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(46, (uint32_t)irq14, 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
  setGate(47, (uint32_t)irq15, 0x08, IDT_FLAG_INTERRUPT_GATE | IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_32BIT);
}
