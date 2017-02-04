#ifndef _KERNEL_GDT_H
#define _KERNEL_GDT_H

#include <stddef.h>

/* Defines a GDT entry. We say packed, because it prevents the
*  compiler from doing things that it thinks is best: Prevent
*  compiler "optimization" by packing */
struct gdt_entry
{
    unsigned short limit_low; // TODO: u16int
    unsigned short base_low; // TODO: u16int
    unsigned char base_middle; // TODO: u8int
    unsigned char access; // TODO: u8int
    unsigned char granularity; // TODO: u8int
    unsigned char base_high; // TODO: u8int
} __attribute__((packed));
typedef struct gdt_entry gdt_entry_t;

/* Special pointer which includes the limit: The max bytes
*  taken up by the GDT, minus 1. Again, this NEEDS to be packed */
struct gdt_ptr
{
    unsigned short limit; // TODO: u16int
    unsigned int base; // TODO: u32int
} __attribute__((packed));
typedef struct gdt_ptr gdt_ptr_t;

/* This will be a function in start.asm. We use this to properly
*  reload the new segment registers */
#if defined(__cplusplus)
extern "C"
#else
extern
#endif
void gdt_flush(unsigned int); // TODO: u32int

#if defined(__cplusplus)
extern "C"
#endif
void gdt_install(void);

#endif
