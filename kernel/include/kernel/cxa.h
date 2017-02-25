#ifndef _KERNEL_CXA
#define _KERNEL_CXA 1

extern "C"
{
    void __cxa_pure_virtual();
    // int __cxa_atexit(void (*destructor) (void *), void *arg, void *dso);
    // void __cxa_finalize(void *f);
}

#endif /* _KERNEL_CXA */
