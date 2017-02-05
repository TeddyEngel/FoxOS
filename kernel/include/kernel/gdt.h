#ifndef _KERNEL_GDT_H
#define _KERNEL_GDT_H

#include <cstdint>

/* Defines a GDT entry. We say packed, because it prevents the
*  compiler from doing things that it thinks is best: Prevent
*  compiler "optimization" by packing */
typedef struct gdt_entry
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed)) gdt_entry_t;

/* Special pointer which includes the limit: The max bytes
*  taken up by the GDT, minus 1. Again, this NEEDS to be packed */
typedef struct gdt_ptr
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) gdt_ptr_t;

class gdt_manager
{
public:
    static void initialize();

private:
    static void set_gate(int32_t, uint32_t, uint32_t, uint8_t, uint8_t);

private:
    static gdt_entry_t entries[];
    static gdt_ptr_t   ptr;
};

/* This will be a function in start.asm. We use this to properly
*  reload the new segment registers */
extern "C"
{
    void gdt_flush(uint32_t);
}

#endif /* _KERNEL_GDT_H */