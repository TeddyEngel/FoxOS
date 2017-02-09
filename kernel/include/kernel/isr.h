/*
** Interface and structures for high level interrupt service routines.
*/

#ifndef _KERNEL_ISR_H
#define _KERNEL_ISR_H

#include <cstdint>

#include <kernel/registers.h>

// Enables registration of callbacks for interrupts or IRQs.
// For IRQs, to ease confusion, use the #defines above as the
// first parameter.
typedef void (*fct_handler)(registers_t);

class isr_manager
{
public:
    static void initialize();

    static bool has_handler(uint8_t);
    static fct_handler get_handler(uint8_t);
    static void register_handler(uint8_t, fct_handler);

private:
    static fct_handler handlers[];
};

extern "C"
{
    void isr_handler(registers_t);
}

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

#endif /* _KERNEL_ISR_H */