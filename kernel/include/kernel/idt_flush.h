#ifndef _KERNEL_IDT_FLUSH_H
#define _KERNEL_IDT_FLUSH_H

#include <cstdint>

extern "C"
{
    void idt_flush(uint32_t);
}

#endif /* _KERNEL_IDT_FLUSH_H */