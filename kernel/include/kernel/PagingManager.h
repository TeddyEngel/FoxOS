// TODO: Implement real bitset class
// TODO: Use real bitset class instead of ad-hoc one

#ifndef _KERNEL_PAGING_MANAGER_H
#define _KERNEL_PAGING_MANAGER_H

#include <kernel/PageTypes.h>
#include <kernel/registers.h>

#include <kernel/bitset.h>

class KernelManager;

class PagingManager
{
public:
    static const char* SERVICE_NAME;
    
public:
    PagingManager(KernelManager&);

    /**
      Sets up the environment, page directories etc and
      enables paging.
    **/
    int initialize();

    /**
      Causes the specified page directory to be loaded into the
      CR3 register.
    **/
    void switchPageDirectory(page_directory_t*);

    page_t* getKernelPage(uint32_t address, int make);
    
    // Handler for page faults.
    void onPageFault(const registers_t&);

    // Allocate a frame
    void allocFrame(page_t*, int isKernel, int isWriteable);
    // Deallocate a frame
    void freeFrame(page_t*);

public:
    // Converts the given value to the nearest page-aligned value
    static uint32_t getNearestPageValue(uint32_t value);

private:
    /**
      Retrieves a pointer to the page required.
      If make == 1, if the page-table in which this page should
      reside isn't created, create it!
    **/
    page_t* getPage(uint32_t address, int make, page_directory_t*);

    // Set a bit in the frames bitset
    void setFrame(uint32_t frameAddress);
    // Clear a bit in the frames bitset
    void clearFrame(uint32_t frameAddress);
    // Test if a bit is set
    uint32_t testFrame(uint32_t frameAddress);
    // Find the first free frames
    uint32_t firstFrame();

private:
    static void onPageFaultHook(const registers_t&);

private:
    KernelManager& _kernelManager;

    // The kernel's page directory
    page_directory_t* _kernelDirectory;

    // The current page directory;
    page_directory_t* _currentDirectory;

    // Bitset of frames
    uint32_t *_frames;
    uint32_t _nframes;
};

#endif /* _KERNEL_PAGING_MANAGER_H */
