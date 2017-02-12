#pragma once

#include <kernel/registers.h>

extern "C"
{
    void isr_handler(registers_t);
}
