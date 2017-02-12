#pragma once

class KernelManager;

class MemoryManager
{
public:
    MemoryManager(KernelManager&);

    void initialize();

private:
    KernelManager& _kernelManager;
};
