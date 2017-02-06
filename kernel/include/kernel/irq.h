/*
** Interface and structures for high level interrupt service routines.
*/

#ifndef _KERNEL_IRQ_H
#define _KERNEL_IRQ_H

#include <cstdint>

#include <kernel/registers.h>

extern "C"
{
    void irq_handler(registers_t);
}

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

// These extern directives let us access the addresses of our ASM ISR handlers.
extern "C"
{
    void irq0();
    void irq1();
    void irq2();
    void irq3();
    void irq4();
    void irq5();
    void irq6();
    void irq7();
    void irq8();
    void irq9();
    void irq10();
    void irq11();
    void irq12();
    void irq13();
    void irq14();
    void irq15();
}

#endif /* _KERNEL_IRQ_H */