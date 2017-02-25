#ifndef _KERNEL_USER_H
#define _KERNEL_USER_H

#include <cstdint>

class KernelManager;

class User
{    
public:
    User(KernelManager&);

    uint32_t getId() const;
    const char* getName() const;

private:
    KernelManager& _kernelManager;
    uint32_t _id;
    const char* _name;
};

#endif /* _KERNEL_USER_H */