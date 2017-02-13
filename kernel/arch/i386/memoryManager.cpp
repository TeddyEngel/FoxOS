#include <kernel/MemoryManager.h>

#include <cstring>
#include <cstdio>
#include <memory>

#include <kernel/KernelManager.h>

extern KernelManager kernelManager;
extern uint32_t placement_address;

MemoryManager::MemoryManager(KernelManager& kernelManager)
    : _kernelManager(kernelManager)
    , _kernelDirectory(NULL)
    , _currentDirectory(NULL)
{

}

void MemoryManager::initialize()
{
    // The size of physical memory. For the moment we
   // assume it is 16MB big.
   uint32_t memEndPage = PHYSICAL_MEMORY_SIZE;

   _nframes = memEndPage / PAGE_SIZE;
   _frames = (uint32_t*)kmalloc(INDEX_FROM_BIT(_nframes));
   memset(_frames, 0, INDEX_FROM_BIT(_nframes));

   // Let's make a page directory.
   _kernelDirectory = (page_directory_t*)kmalloc_a(sizeof(page_directory_t));
   memset(_kernelDirectory, 0, sizeof(page_directory_t));
   _currentDirectory = _kernelDirectory;

   // We need to identity map (phys addr = virt addr) from
   // 0x0 to the end of used memory, so we can access this
   // transparently, as if paging wasn't enabled.
   // NOTE that we use a while loop here deliberately.
   // inside the loop body we actually change placement_address
   // by calling kmalloc(). A while loop causes this to be
   // computed on-the-fly rather than once at the start.
   
   uint32_t i = 0;
   while (i < placement_address)
   {
       // Kernel code is readable but not writeable from userspace.
       allocFrame(getPage(i, 1, _kernelDirectory), 0, 0);
       i += PAGE_SIZE;
   }

   // Before we enable paging, we must register our page fault handler.
   _kernelManager.getInterruptManager().registerHandler(14, onPageFaultHook);

   // Now, enable paging!
   switchPageDirectory(_kernelDirectory);
}

void MemoryManager::switchPageDirectory(page_directory_t* dir)
{
    _currentDirectory = dir;
    asm volatile("mov %0, %%cr3":: "r"(&dir->tablesPhysical));
    uint32_t cr0;
    asm volatile("mov %%cr0, %0": "=r"(cr0));
    cr0 |= 0x80000000; // Enable paging!
    asm volatile("mov %0, %%cr0":: "r"(cr0));
}

page_t* MemoryManager::getPage(uint32_t address, int make, page_directory_t* dir)
{
    // Turn the address into an index.
    address /= PAGE_SIZE;
    // Find the page table containing this address.
    uint32_t table_idx = address / PAGE_TABLES_PER_DIRECTORY;
    if (dir->tables[table_idx]) // If this table is already assigned
       return &dir->tables[table_idx]->pages[address % PAGES_PER_TABLE];
    else if(make)
    {
       uint32_t tmp;
       dir->tables[table_idx] = (page_table_t*)kmalloc_ap(sizeof(page_table_t), &tmp);
       memset(dir->tables[table_idx], 0, PAGE_SIZE);
       dir->tablesPhysical[table_idx] = tmp | 0x7; // PRESENT, RW, US.
       return &dir->tables[table_idx]->pages[address % PAGES_PER_TABLE];
    }
    return NULL;
}

void MemoryManager::onPageFault()
{
}

void MemoryManager::onPageFaultHook(registers_t)
{
    kernelManager.getMemoryManager().onPageFault();
}

void MemoryManager::setFrame(uint32_t frameAddress)
{
   uint32_t frame = frameAddress / PAGE_SIZE;
   uint32_t idx = INDEX_FROM_BIT(frame);
   uint32_t off = OFFSET_FROM_BIT(frame);
   _frames[idx] |= (0x1 << off);
}

void MemoryManager::clearFrame(uint32_t frameAddress)
{
   uint32_t frame = frameAddress / PAGE_SIZE;
   uint32_t idx = INDEX_FROM_BIT(frame);
   uint32_t off = OFFSET_FROM_BIT(frame);
   _frames[idx] &= ~(0x1 << off);
}

uint32_t MemoryManager::testFrame(uint32_t frameAddress)
{
   uint32_t frame = frameAddress / PAGE_SIZE;
   uint32_t idx = INDEX_FROM_BIT(frame);
   uint32_t off = OFFSET_FROM_BIT(frame);
   return (_frames[idx] & (0x1 << off));
}

uint32_t MemoryManager::firstFrame()
{
   uint32_t i, j;

   for (i = 0; i < INDEX_FROM_BIT(_nframes); i++)
   {
       if (_frames[i] != 0xFFFFFFFF) // nothing free, exit early.
       {
           // at least one bit is free here.
           for (j = 0; j < 32; j++)
           {
               uint32_t toTest = 0x1 << j;
               if ( !(_frames[i]&toTest) )
               {
                   return i * 4 * 8 + j;
               }
           }
       }
   }
} 

void MemoryManager::allocFrame(page_t* page, int isKernel, int isWriteable)
{
   if (page->frame != NULL)
       return; // Frame was already allocated, return straight away.
   else
   {
       uint32_t idx = firstFrame(); // idx is now the index of the first free frame.

       if (idx == (uint32_t)-1)
           _kernelManager.panic("No free frames!");
       setFrame(idx * PAGE_SIZE); // this frame is now ours!
       page->present = 1; // Mark it as present.
       page->rw = isWriteable ? 1 : 0; // Should the page be writeable?
       page->user = isKernel ? 0 : 1; // Should the page be user-mode?
       page->frame = idx;
   }
}

void MemoryManager::freeFrame(page_t *page)
{
   uint32_t frame;
   if (!(frame = page->frame))
       return; // The given page didn't actually have an allocated frame!
   else
   {
       clearFrame(frame); // Frame is now free again.
       page->frame = NULL; // Page now doesn't have a frame.
   }
} 