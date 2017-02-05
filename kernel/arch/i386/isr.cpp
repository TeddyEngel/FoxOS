#include <kernel/isr.h>

#include <cstdio>

void isr_handler(registers_t regs)
{
    printf("Interrupt: %d %d\n", regs.int_no, regs.err_code);
}