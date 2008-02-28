
#include <util/XMemory.h>
#include <assert.h>
#include "util/BOEPlatformUtils.H"

_bt_begin

void* XMemory::operator new(size_t size)
{
	size_t headerSize = BOEPlatformUtils::alignPointerForNewBlockAllocation(
										sizeof(BT_Memory_Base*));
	
    void* const block = BOEPlatformUtils::fgMemoryManager->calloc
        (
	        headerSize + size
        );
    *(BT_Memory_Base**)block = BOEPlatformUtils::fgMemoryManager;

    return (char*)block + headerSize;
}

#if defined(BOE_VISUALCPP)

void* XMemory::operator new(size_t size, const char* file, int line)
{ 
		 return operator new(size); 
}
 
void XMemory::operator delete(void* p, const char* file, int line)
{ 
		 operator delete(p); 
}
 
#endif

void* XMemory::operator new(size_t size, BT_Memory_Base* manager)
{
    assert(manager != 0);
	
	size_t headerSize = BOEPlatformUtils::alignPointerForNewBlockAllocation(
										sizeof(BT_Memory_Base*));
    void* const block = manager->calloc(headerSize + size);
    *(BT_Memory_Base**)block = manager;

    return (char*)block + headerSize;
}

void XMemory::operator delete(void* p)
{
    if (p != 0)
    {
		size_t headerSize = BOEPlatformUtils::alignPointerForNewBlockAllocation(
											sizeof(BT_Memory_Base*));
        void* const block = (char*)p - headerSize;

        BT_Memory_Base* const manager = *(BT_Memory_Base**)block;
        assert(manager != 0);
        manager->free(block);
    }
}

//The Borland compiler is complaining about duplicate overloading of delete
#if !defined(BOE_BORLAND)

void XMemory::operator delete(void* p, BT_Memory_Base* manager)
{
    assert(manager != 0);
	
    if (p != 0)
    {
        size_t headerSize = BOEPlatformUtils::alignPointerForNewBlockAllocation(sizeof(BT_Memory_Base*));
        void* const block = (char*)p - headerSize;


        BT_Memory_Base* pM = *(BT_Memory_Base**)block;
        pM->free(block);
    }
}

_bt_end

#endif


