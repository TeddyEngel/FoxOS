#pragma once

#include <cstdint>

#define GDT_ENTRIES      5
// #define GDT_FLAG_DATASEG 0x02
// #define GDT_FLAG_CODESEG 0x0a
// #define GDT_FLAG_TSS     0x09

// #define GDT_FLAG_SEGMENT 0x10
// #define GDT_FLAG_RING0   0x00
// #define GDT_FLAG_RING3   0x60
// #define GDT_FLAG_PRESENT 0x80

// #define GDT_FLAG_4K      0x800
// #define GDT_FLAG_32_BIT  0x400

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
