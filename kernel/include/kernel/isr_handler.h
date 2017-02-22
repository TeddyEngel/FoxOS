#ifndef _KERNEL_ISR_HANDLER_H
#define _KERNEL_ISR_HANDLER_H

#include <kernel/registers.h>

extern "C"
{
    void isr_handler(registers_t);
}

#endif /* _KERNEL_ISR_HANDLER_H */