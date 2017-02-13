#include <kernel/CpuManager.h>

#include <kernel/KernelManager.h>

CpuManager::CpuManager(KernelManager& kernelManager)
    : _kernelManager(kernelManager)
{

}

void CpuManager::halt()
{
    asm volatile("hlt");
}
