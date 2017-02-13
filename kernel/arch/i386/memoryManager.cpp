#include <kernel/MemoryManager.h>

#include <kernel/KernelManager.h>

MemoryManager::MemoryManager(KernelManager& kernelManager)
    : _kernelManager(kernelManager)
{

}

void MemoryManager::initialize()
{
}

void MemoryManager::switchPageDirectory(page_directory_t*)
{
}

page_t* MemoryManager::getPage(uint32_t address, int make, page_directory_t*)
{
    (void)address;
    (void)make;
    return NULL;
}

void MemoryManager::onPageFault(registers_t regs)
{
    (void)regs;
}

void MemoryManager::setFrame(uint32_t frameAddress)
{
   uint32_t frame = frameAddress/0x1000;
   uint32_t idx = INDEX_FROM_BIT(frame);
   uint32_t off = OFFSET_FROM_BIT(frame);
   _frames[idx] |= (0x1 << off);
}

void MemoryManager::clearFrame(uint32_t frameAddress)
{
   uint32_t frame = frameAddress/0x1000;
   uint32_t idx = INDEX_FROM_BIT(frame);
   uint32_t off = OFFSET_FROM_BIT(frame);
   _frames[idx] &= ~(0x1 << off);
}

uint32_t MemoryManager::testFrame(uint32_t frameAddress)
{
   uint32_t frame = frameAddress/0x1000;
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
                   return i*4*8+j;
               }
           }
       }
   }
} 