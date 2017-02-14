/*
** Timer to handle the system clock / IRQ0
*/

#ifndef _KERNEL_TIMER_MANAGER_H
#define _KERNEL_TIMER_MANAGER_H

#include <cstdint>

#include <kernel/registers.h>

class KernelManager;

class TimerManager
{
public:
    static const char* SERVICE_NAME;
    
public:
    TimerManager(KernelManager&);
    int initialize();
    void increaseTicks();

    void onTick();

private:
    // TODO: Change to bind / lambdas once I support them
    static void onTickHook(registers_t);

private:
    static const uint32_t FREQUENCY;

private:
    KernelManager& _kernelManager;
    uint32_t _tick;
};

#endif /* _KERNEL_TIMER_MANAGER_H */