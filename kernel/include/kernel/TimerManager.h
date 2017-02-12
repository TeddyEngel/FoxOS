/*
** Timer to handle the system clock / IRQ0
*/

#ifndef _KERNEL_TIMER_MANAGER_H
#define _KERNEL_TIMER_MANAGER_H

#include <cstdint>

#include <kernel/registers.h>

class TimerManager
{
public:
    TimerManager();
    void initialize();
    void increaseTicks();

    void onTick();

private:
    // TODO: Change to bind / lambdas once I support them
    static void onTickHook(registers_t);

private:
    static const uint32_t FREQUENCY;

private:
    uint32_t _tick;
};

#endif /* _KERNEL_TIMER_MANAGER_H */