#include <kernel/TimerManager.h>

#include <cstdio>

#include <kernel/InterruptManager.h>
#include <kernel/irq_types.h>
#include <kernel/KernelManager.h>
#include <kernel/pit_types.h>

extern KernelManager kernelManager;

const char* TimerManager::SERVICE_NAME = "Timer";
const uint32_t TimerManager::FREQUENCY = 50;

TimerManager::TimerManager(KernelManager& kernelManager)
    : _kernelManager(kernelManager)
    , _tick(0)
{
}

int TimerManager::initialize()
{
    // Firstly, register our timer callback.
    InterruptManager& interruptManager = _kernelManager.getInterruptManager();
    interruptManager.registerHandler(IRQ0, &onTickHook);

    // The value we send to the PIT is the value to divide it's input clock
    // (1193180 Hz) by, to get our required frequency. Important to note is
    // that the divisor must be small enough to fit into 16-bits.
    uint32_t divisor = 1193180 / FREQUENCY;

    // Send the command byte.
    outb(PIT_COMMAND_PORT, PIT_REPEATING_MODE);

    // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
    uint8_t l = (uint8_t)(divisor & 0xFF);
    uint8_t h = (uint8_t)((divisor >> 8) & 0xFF);

    // Send the frequency divisor.
    outb(PIT_DATA_PORT_CHANNEL_0, l);
    outb(PIT_DATA_PORT_CHANNEL_0, h);

    return 0;
} 

void TimerManager::onTick()
{
    ++_tick;
    // printf("Tick: %d\n", _tick);
}

void TimerManager::onTickHook(registers_t)
{
    TimerManager& timerManager = kernelManager.getTimerManager();
    timerManager.onTick();
}
