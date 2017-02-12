#include <kernel/MemoryManager.h>

#include <kernel/KernelManager.h>

MemoryManager::MemoryManager(KernelManager& kernelManager)
    : _kernelManager(kernelManager)
{

}

void MemoryManager::initialize()
{
}