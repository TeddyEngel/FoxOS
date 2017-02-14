#ifndef _KERNEL_IDT_H
#define _KERNEL_IDT_H

#include <cstdint>

#include <kernel/idt_types.h>
#include <kernel/idt_flush.h>
#include <kernel/isr_handlers.h>

class KernelManager;

class InterruptManager
{
public:
    static const char* SERVICE_NAME;
    
public:
    InterruptManager(KernelManager&);
    int initialize();

    void enableInterrupts();
    void disableInterrupts();
    bool areInterruptsEnabled();

    bool hasHandler(uint8_t n);
    fct_handler getHandler(uint8_t n);
    void registerHandler(uint8_t n, fct_handler);

private:
    void remapIrqs(int32_t offset1, int32_t offset2);
    void setGate(uint8_t, uint32_t, uint16_t, uint8_t);
    void setCpuGates();
    void setIrqGates();

private:
    KernelManager& _kernelManager;
    idt_entry_t _entries[IDT_ENTRIES];
    idt_ptr_t   _ptr;
    fct_handler _handlers[IDT_ENTRIES];
};

#endif /* _KERNEL_IDT_H */