#include <kernel/GdtManager.h>

#include <kernel/KernelManager.h>

const char* GdtManager::SERVICE_NAME = "GDT";

GdtManager::GdtManager(KernelManager& kernelManager)
    : _kernelManager(kernelManager)
{
}

/* Should be called by main. This will setup the special GDT
*  pointer, set up the first 3 entries in our GDT, and then
*  finally call gdt_flush() in our assembler file in order
*  to tell the processor where the new GDT is and update the
*  new segment registers */
int GdtManager::initialize()
{
    // Setup the GDT pointer and limit
    _ptr.limit = (sizeof(gdt_entry_t) * GDT_ENTRIES) - 1;
    _ptr.base = (uint32_t)&_entries;

    // Our NULL descriptor
    setGate(0, 0, 0, 0, 0);

    /* The second entry is our Code Segment. The base address
    *  is 0, the limit is 4GBytes, it uses 4KByte granularity,
    *  uses 32-bit opcodes, and is a Code Segment descriptor.
    *  Please check the table above in the tutorial in order
    *  to see exactly what each value means */
    // setGate(1, 0, 0xFFFFFFFF, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_CODESEG | GDT_FLAG_4K | GDT_FLAG_PRESENT | GDT_FLAG_RING0);
    setGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    /* The third entry is our Data Segment. It's EXACTLY the
    *  same as our code segment, but the descriptor type in
    *  this entry's access byte says it's a Data Segment */
    setGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    // setGate(2, 0, 0xFFFFFFFF, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_DATASEG | GDT_FLAG_4K | GDT_FLAG_PRESENT | GDT_FLAG_RING0);

    // User mode code segment
    setGate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    // setGate(3, 0, 0xFFFFFFFF, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_CODESEG | GDT_FLAG_4K | GDT_FLAG_PRESENT | GDT_FLAG_RING3);

    // User mode data segment 
    setGate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
    // setGate(4, 0, 0xFFFFFFFF, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_DATASEG | GDT_FLAG_4K | GDT_FLAG_PRESENT | GDT_FLAG_RING3);

    /* Flush out the old GDT and install the new changes! */
    nativeLoadGdt();
    // TODO: Make the following work with inline assembly :/
    /*
    __asm__ __volatile__ (
        "movl $0x10, %%eax\n"
        "movl %%eax, %%ds\n"
        "movl %%eax, %%es\n"
        "movl %%eax, %%fs\n"
        "movl %%eax, %%gs\n"
        "movl %%eax, %%ss\n"
    :
    :
    :"%eax"
    );
    */
    gdt_flush();

    return 0;
}

inline void GdtManager::nativeLoadGdt()
{
    __asm__ __volatile__("lgdt %[in]"::[in]"m" (_ptr));
}

void GdtManager::setGate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    if(num >= GDT_ENTRIES)
        return;

    /* Setup the descriptor base address */
    _entries[num].base_low = (base & 0xFFFF);
    _entries[num].base_middle = (base >> 16) & 0xFF;
    _entries[num].base_high = (base >> 24) & 0xFF;

    /* Setup the descriptor limits */
    _entries[num].limit_low = (limit & 0xFFFF);
    _entries[num].granularity = ((limit >> 16) & 0x0F);

    /* Finally, set up the granularity and access flags */
    _entries[num].granularity |= (gran & 0xF0);
    _entries[num].access = access;
}
