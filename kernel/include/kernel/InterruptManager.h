#ifndef _KERNEL_IDT_H
#define _KERNEL_IDT_H

#include <cstdint>

#include <kernel/idt_types.h>
#include <kernel/idt_flush.h>

class InterruptManager
{
public:
    InterruptManager();
    void initialize();
    void enableInterrupts();
    void disableInterrupts();
    bool areInterruptsEnabled();

private:
    void remapIrqs(int32_t offset1, int32_t offset2);
    void setGate(uint8_t, uint32_t, uint16_t, uint8_t);
    void setCpuGates();
    void setIrqGates();

private:
    idt_entry_t entries[IDT_ENTRIES];
    idt_ptr_t   ptr;
};

#endif /* _KERNEL_IDT_H */