#ifndef _KERNEL_USER_H
#define _KERNEL_USER_H

#include <cstdint>

class KernelManager;

class User
{    
public:
    User(KernelManager&);

    uint32_t getId() const;
    char* getName() const;

private: // TODO: Make getters setters once this is fixed, or not?
    KernelManager& _kernelManager;
    uint32_t _id;
    char* _name;
};

#endif /* _KERNEL_USER_H */