#include <kernel/User.h>

#include <cstdio>
#include <cstring>

#include <kernel/KernelManager.h>

User::User(KernelManager& kernelManager)
  : _kernelManager(kernelManager)
  , _id(0)
  , _name("root")
{
}

uint32_t User::getId() const
{
    return _id;
}

char* User::getName() const
{
    return _name;
}