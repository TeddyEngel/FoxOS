#include <kernel/gdt.h>

// Our GDT entries: code and data for kernel, code and data for user mode, null entry
gdt_entry_t gdt_entries[5];
gdt_ptr_t gp;

/* Setup a descriptor in the Global Descriptor Table */
void gdt_set_gate(int num, unsigned long base, unsigned long limit,
                           unsigned char access, unsigned char gran)
{
    /* Setup the descriptor base address */
    gdt_entries[num].base_low = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high = (base >> 24) & 0xFF;

    /* Setup the descriptor limits */
    gdt_entries[num].limit_low = (limit & 0xFFFF);
    gdt_entries[num].granularity = ((limit >> 16) & 0x0F);

    /* Finally, set up the granularity and access flags */
    gdt_entries[num].granularity |= (gran & 0xF0);
    gdt_entries[num].access = access;
}

/* Should be called by main. This will setup the special GDT
*  pointer, set up the first 3 entries in our GDT, and then
*  finally call gdt_flush() in our assembler file in order
*  to tell the processor where the new GDT is and update the
*  new segment registers */
void gdt_install()
{
    // Setup the GDT pointer and limit
    gp.limit = (sizeof(gdt_entry_t) * 5) - 1;
    gp.base = (unsigned int)&gdt_entries;

    // Our NULL descriptor
    gdt_set_gate(0, 0, 0, 0, 0);

    /* The second entry is our Code Segment. The base address
    *  is 0, the limit is 4GBytes, it uses 4KByte granularity,
    *  uses 32-bit opcodes, and is a Code Segment descriptor.
    *  Please check the table above in the tutorial in order
    *  to see exactly what each value means */
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    /* The third entry is our Data Segment. It's EXACTLY the
    *  same as our code segment, but the descriptor type in
    *  this entry's access byte says it's a Data Segment */
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    // User mode code segment
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);

    // User mode data segment 
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    /* Flush out the old GDT and install the new changes! */
    gdt_flush((unsigned int)&gp);
}