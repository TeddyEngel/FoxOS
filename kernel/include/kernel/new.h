#ifndef _KERNEL_NEW_H
#define _KERNEL_NEW_H

#include <cstddef>

void* operator new(std::size_t sz);

#endif /* _KERNEL_NEW_H */