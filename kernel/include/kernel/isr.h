/*
** Interface and structures for high level interrupt service routines.
*/

#ifndef _KERNEL_ISR_H
#define _KERNEL_ISR_H

#include <cstdint>

typedef struct registers
{
   uint32_t ds;                  // Data segment selector
   uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
   uint32_t int_no, err_code;    // Interrupt number and error code (if applicable)
   uint32_t eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
} registers_t; 

extern "C"
{
    void isr_handler(registers_t);
}

#endif /* _KERNEL_ISR_H */