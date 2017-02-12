/*
** Timer to handle the system clock / IRQ0
*/

#pragma once

#include <cstdint>

#include <kernel/registers.h>

class KernelManager;

class TimerManager
{
public:
    TimerManager(KernelManager&);
    void initialize();
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
