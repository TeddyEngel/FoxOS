#ifndef _KERNEL_MEMORY_MANAGER_H
#define _KERNEL_MEMORY_MANAGER_H

#include <kernel/PageTypes.h>
#include <kernel/registers.h>

#include <kernel/bitset.h>

class KernelManager;

class MemoryManager
{
public:
    MemoryManager(KernelManager&);

    /**
      Sets up the environment, page directories etc and
      enables paging.
    **/
    void initialize();

    /**
      Causes the specified page directory to be loaded into the
      CR3 register.
    **/
    void switchPageDirectory(page_directory_t*);

    /**
      Retrieves a pointer to the page required.
      If make == 1, if the page-table in which this page should
      reside isn't created, create it!
    **/
    page_t *getPage(uint32_t address, int make, page_directory_t*);

    /**
      Handler for page faults.
    **/
    void onPageFault(registers_t regs); 

private:
    // Set a bit in the frames bitset
    void setFrame(uint32_t frameAddr);
    // Clear a bit in the frames bitset
    void clearFrame(uint32_t frameAddr);
    // Test if a bit is set.
    uint32_t testFrame(uint32_t frameAddr);
    // Find the first free frames
    uint32_t firstFrame();

private:
    KernelManager& _kernelManager;

    // Bitset of frames
    uint32_t *_frames;
    uint32_t _nframes;
};

#endif /* _KERNEL_MEMORY_MANAGER_H */
