#ifndef _KERNEL_H
#define _KERNEL_H

#include <kernel/new.h>
#include <kernel/delete.h>

extern "C"
{
   void kernelEarly();
   void kernelMain();
}

#endif /* _KERNEL_H */