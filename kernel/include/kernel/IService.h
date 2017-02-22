/*
** Generic Kernel Service
** TODO: Implement vtables!
*/

#ifndef _KERNEL_I_SERVICE_H
#define _KERNEL_I_SERVICE_H

class KernelManager;

class IService
{    
public:
    IService(KernelManager& kernelManager)
        : _kernelManager(kernelManager)
    {
    };

    virtual int initialize() = 0;

protected:
    KernelManager& _kernelManager;
};

#endif /* _KERNEL_I_SERVICE_H */