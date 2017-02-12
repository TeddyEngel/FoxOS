#include <kernel/MemoryManager.h>

#include <kernel/KernelManager.h>

MemoryManager::MemoryManager(KernelManager& kernelManager)
    : _kernelManager(kernelManager)
{

}

void MemoryManager::initialize()
{
}

void MemoryManager::switchPageDirectory(page_directory_t*)
{
}

page_t *MemoryManager::getPage(uint32_t address, int make, page_directory_t*)
{
}

void MemoryManager::onPageFault(registers_t regs)
{
}