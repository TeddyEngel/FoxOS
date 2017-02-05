#include <kernel/gdt.h>

gdt_entry_t gdt_manager::entries[GDT_ENTRIES];
gdt_ptr_t   gdt_manager::ptr;

/* Should be called by main. This will setup the special GDT
*  pointer, set up the first 3 entries in our GDT, and then
*  finally call gdt_flush() in our assembler file in order
*  to tell the processor where the new GDT is and update the
*  new segment registers */
void gdt_manager::initialize()
{
    // Setup the GDT pointer and limit
    ptr.limit = (sizeof(gdt_entry_t) * GDT_ENTRIES) - 1;
    ptr.base = (uint32_t)&entries;

    // Our NULL descriptor
    set_gate(0, 0, 0, 0, 0);

    // set_gate(1, 0, 0xFFFFFFFF, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_CODESEG | GDT_FLAG_4K | GDT_FLAG_PRESENT | GDT_FLAG_RING0);
    // set_gate(2, 0, 0xFFFFFFFF, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_DATASEG | GDT_FLAG_4K | GDT_FLAG_PRESENT | GDT_FLAG_RING0);
    // set_gate(3, 0, 0xFFFFFFFF, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_CODESEG | GDT_FLAG_4K | GDT_FLAG_PRESENT | GDT_FLAG_RING3);
    // set_gate(4, 0, 0xFFFFFFFF, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_DATASEG | GDT_FLAG_4K | GDT_FLAG_PRESENT | GDT_FLAG_RING3);

    /* The second entry is our Code Segment. The base address
    *  is 0, the limit is 4GBytes, it uses 4KByte granularity,
    *  uses 32-bit opcodes, and is a Code Segment descriptor.
    *  Please check the table above in the tutorial in order
    *  to see exactly what each value means */
    // set_gate(1, 0, 0xFFFFFFFF, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_CODESEG | GDT_FLAG_4K | GDT_FLAG_PRESENT | GDT_FLAG_RING0);
    set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    /* The third entry is our Data Segment. It's EXACTLY the
    *  same as our code segment, but the descriptor type in
    *  this entry's access byte says it's a Data Segment */
    set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    // set_gate(2, 0, 0xFFFFFFFF, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_DATASEG | GDT_FLAG_4K | GDT_FLAG_PRESENT | GDT_FLAG_RING0);

    // User mode code segment
    set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    // set_gate(3, 0, 0xFFFFFFFF, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_CODESEG | GDT_FLAG_4K | GDT_FLAG_PRESENT | GDT_FLAG_RING3);

    // User mode data segment 
    set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
    // set_gate(4, 0, 0xFFFFFFFF, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_DATASEG | GDT_FLAG_4K | GDT_FLAG_PRESENT | GDT_FLAG_RING3);

    /* Flush out the old GDT and install the new changes! */
    gdt_flush((uint32_t)&ptr);
}

/* Setup a descriptor in the Global Descriptor Table */
void gdt_manager::set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    if(num >= GDT_ENTRIES)
        return;
    // uint64_t *gdt_cp;
    // gdt_cp = (gdt + i);
    // *gdt_cp = limit & 0xffffLL;
    // *gdt_cp |= (base & 0xffffffLL) << 16;
    // *gdt_cp |= (flags & 0xffLL) << 40;
    // *gdt_cp |= ((limit & 0xf0000LL) >> 16) << 48;
    // *gdt_cp |= ((flags & 0xf00LL) >> 8) << 52;
    // *gdt_cp |= ((base & 0xff000000LL) >> 24) << 56;

    /* Setup the descriptor base address */
    entries[num].base_low = (base & 0xFFFF);
    entries[num].base_middle = (base >> 16) & 0xFF;
    entries[num].base_high = (base >> 24) & 0xFF;

    /* Setup the descriptor limits */
    entries[num].limit_low = (limit & 0xFFFF);
    entries[num].granularity = ((limit >> 16) & 0x0F);

    /* Finally, set up the granularity and access flags */
    entries[num].granularity |= (gran & 0xF0);
    entries[num].access = access;
}
