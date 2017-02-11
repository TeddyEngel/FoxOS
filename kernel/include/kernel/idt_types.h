#ifndef _KERNEL_IDT_TYPES_H
#define _KERNEL_IDT_TYPES_H

#include <cstdint>

#include <kernel/registers.h>

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

// Enables registration of callbacks for interrupts or IRQs.
// For IRQs, to ease confusion, use the #defines above as the
// first parameter.
typedef void (*fct_handler)(registers_t);

#endif /* _KERNEL_IDT_TYPES_H */