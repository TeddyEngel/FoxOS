#ifndef _KERNEL_IDT_H
#define _KERNEL_IDT_H

#include <cstdint>

// A struct describing an interrupt gate.
struct idt_entry
{
   uint16_t base_lo;             // The lower 16 bits of the address to jump to when this interrupt fires.
   uint16_t sel;                 // Kernel segment selector.
   uint8_t  always0;             // This must always be zero.
   uint8_t  flags;               // More flags. See documentation.
   uint16_t base_hi;             // The upper 16 bits of the address to jump to.
} __attribute__((packed));
typedef struct idt_entry idt_entry_t;

// A struct describing a pointer to an array of interrupt handlers.
// This is in a format suitable for giving to 'lidt'.
struct idt_ptr
{
   uint16_t limit;
   uint32_t base;                // The address of the first element in our idt_entry_t array.
} __attribute__((packed));
typedef struct idt_ptr idt_ptr_t;

class idt_manager
{
public:
    static void initialize();
    static void set_gate(uint8_t, uint32_t, uint16_t, uint8_t);

private:
    static idt_entry_t entries[];
    static idt_ptr_t   ptr;
};

// These extern directives let us access the addresses of our ASM ISR handlers.
// extern void isr0();
// ...
// extern void isr31(); 

extern "C"
{
    void idt_flush(uint32_t);
}

#endif /* _KERNEL_IDT_H */