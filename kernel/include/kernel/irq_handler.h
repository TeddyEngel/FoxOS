#ifndef _KERNEL_IRQ_HANDLER_H
#define _KERNEL_IRQ_HANDLER_H

#include <kernel/registers.h>

extern "C"
{
    void irq_handler(registers_t*);
}

#endif /* _KERNEL_IRQ_HANDLER_H */