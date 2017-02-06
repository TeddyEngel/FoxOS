#include <kernel/isr.h>

#include <cstdio>

#include <kernel/idt.h>

fct_handler isr_manager::handlers[IDT_ENTRIES] = { 0 };

void isr_manager::initialize()
{
    //TODO: Register handlers we want to have
}

bool isr_manager::has_handler(uint8_t n)
{
    return handlers[n] != 0;
}

fct_handler isr_manager::get_handler(uint8_t n)
{
    return handlers[n];
}

void isr_manager::register_handler(uint8_t n, fct_handler handler)
{
    handlers[n] = handler;
}

void isr_handler(registers_t regs)
{
    printf("Interrupt: %d %d\n", regs.int_no, regs.err_code);
}