#ifndef _KERNEL_PROCESS_H
#define _KERNEL_PROCESS_H

#include <cstdint>

class KernelManager;

class Process
{    
public:
    Process(KernelManager&);

    uint32_t getId() const;
    const char* getName() const;

private:
    KernelManager& _kernelManager;
    uint32_t _id;
    const char* _name;
};

#endif /* _KERNEL_PROCESS_H */