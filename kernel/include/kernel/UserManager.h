#ifndef _KERNEL_USER_MANAGER_H
#define _KERNEL_USER_MANAGER_H

#include <cstdint>

#include <kernel/User.h>

class KernelManager;

class UserManager
{
public:
    static const char* SERVICE_NAME;

public:
    UserManager(KernelManager&);
    int initialize();

public: // TODO: Make getters setters once this is fixed, or not?
    KernelManager& _kernelManager;
    User _root; //TODO: Replace by dyn table once it's possible
    User& _activeUser;
};

#endif /* _KERNEL_USER_MANAGER_H */