#ifndef _KERNEL_GDT_FLUSH_H
#define _KERNEL_GDT_FLUSH_H

#include <cstdint>

/* This will be a function in start.asm. We use this to properly
*  reload the new segment registers */
extern "C"
{
    void gdt_flush();
}

#endif /* _KERNEL_GDT_FLUSH_H */