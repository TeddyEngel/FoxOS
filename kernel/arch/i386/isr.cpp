#include <kernel/isr.h>

#include <cstdio>

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t regs)
{
    printf("recieved interrupt\n");
    // printf("recieved interrupt: %d\n", regs.int_no);
}