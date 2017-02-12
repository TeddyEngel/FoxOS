#ifndef _KERNEL_GDT_MANAGER_H
#define _KERNEL_GDT_MANAGER_H

#include <cstdint>

#include <kernel/gdt_types.h>
#include <kernel/gdt_flush.h>

class KernelManager;

class GdtManager
{
public:
    GdtManager(KernelManager&);
    void initialize();

private:
    void setGate(int32_t, uint32_t, uint32_t, uint8_t, uint8_t);

private:
    KernelManager& _kernelManager;
    gdt_entry_t _entries[GDT_ENTRIES];
    gdt_ptr_t   _ptr;
};

#endif /* _KERNEL_GDT_MANAGER_H */