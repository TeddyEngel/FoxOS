#include <kernel/UserManager.h>

#include <cstdio>
#include <cstring>

#include <kernel/KernelManager.h>

const char* UserManager::SERVICE_NAME = "Users";

UserManager::UserManager(KernelManager& kernelManager)
  : _kernelManager(kernelManager)
  , _root(_kernelManager)
  , _activeUser(_root)
{
}

int UserManager::initialize()
{
  return 0;
}
