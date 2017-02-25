#include <kernel/Process.h>

#include <kernel/KernelManager.h>

Process::Process(KernelManager& kernelManager)
  : _kernelManager(kernelManager)
  , _id(0)
  , _name("bash")
{
}

uint32_t Process::getId() const
{
    return _id;
}

const char* Process::getName() const
{
    return _name;
}