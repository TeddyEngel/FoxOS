#ifndef _KERNEL_IDT_H
#define _KERNEL_IDT_H

#include <cstdint>

#define IDT_ENTRIES 256

#define IDT_FLAG_PRESENT 0x80

#define IDT_FLAG_RING0 0x00
#define IDT_FLAG_RING3 0x60

#define IDT_FLAG_32BIT 0x8

#define IDT_FLAG_INTERRUPT_GATE 0x6
#define IDT_FLAG_TRAP_GATE 0x7
#define IDT_FLAG_TASK_GATE 0x5

#define IDT_SELECTOR_RING0 0x0
#define IDT_SELECTOR_RING3 0x3
#define IDT_SELECTOR_GDT 0x0
#define IDT_SELECTOR_LDT 0x4

#define PIC1    0x20    /* IO base address for master PIC */
#define PIC2    0xA0    /* IO base address for slave PIC */
#define PIC1_COMMAND  PIC1
#define PIC1_DATA (PIC1+1)
#define PIC2_COMMAND  PIC2
#define PIC2_DATA (PIC2+1)

#define ICW1_ICW4 0x01    //ICW4 (not) needed
#define ICW1_SINGLE 0x02    // Single (cascade) mode
#define ICW1_INTERVAL4  0x04    // Call address interval 4 (8)
#define ICW1_LEVEL  0x08    // Level triggered (edge) mode
#define ICW1_INIT 0x10    // Initialization - required!
 
#define ICW4_8086 0x01    // 8086/88 (MCS-80/85) mode
#define ICW4_AUTO 0x02    // Auto (normal) EOI
#define ICW4_BUF_SLAVE  0x08    // Buffered mode/slave
#define ICW4_BUF_MASTER 0x0C    // Buffered mode/master
#define ICW4_SFNM 0x10    // Special fully nested (not)

// A struct describing an interrupt gate.
typedef struct idt_entry
{
   uint16_t base_lo;             // The lower 16 bits of the address to jump to when this interrupt fires.
   uint16_t sel;                 // Kernel segment selector.
   uint8_t  always0;             // This must always be zero.
   uint8_t  flags;               // More flags. See documentation.
   uint16_t base_hi;             // The upper 16 bits of the address to jump to.
} __attribute__((packed)) idt_entry_t;

// A struct describing a pointer to an array of interrupt handlers.
// This is in a format suitable for giving to 'lidt'.
typedef struct idt_ptr
{
   uint16_t limit;
   uint32_t base;                // The address of the first element in our idt_entry_t array.
} __attribute__((packed)) idt_ptr_t;

class idt_manager
{
public:
    static void initialize();
    static bool are_interrupts_enabled();
    
private:
    static void remap_irqs(int offset1, int offset2);
    static void set_gate(uint8_t, uint32_t, uint16_t, uint8_t);
    
private:
    static idt_entry_t entries[];
    static idt_ptr_t   ptr;
};

// These extern directives let us access the addresses of our ASM ISR handlers.
extern "C"
{
    void isr0();
    void isr1();
    void isr2();
    void isr3();
    void isr4();
    void isr5();
    void isr6();
    void isr7();
    void isr8();
    void isr9();
    void isr10();
    void isr11();
    void isr12();
    void isr13();
    void isr14();
    void isr15();
    void isr16();
    void isr17();
    void isr18();
    void isr19();
    void isr20();
    void isr21();
    void isr22();
    void isr23();
    void isr24();
    void isr25();
    void isr26();
    void isr27();
    void isr28();
    void isr29();
    void isr30();
    void isr31();
}

extern "C"
{
    void idt_flush(uint32_t);
}

#endif /* _KERNEL_IDT_H */