
#include "util/BOEPlatformUtils.h"

_bt BT_Memory_Base* BOEPlatformUtils::fgMemoryManager = 0;

size_t BOEPlatformUtils::alignPointerForNewBlockAllocation(size_t ptrSize)
{
	//	Macro XML_PLATFORM_NEW_BLOCK_ALIGNMENT may be defined
	//	as needed to dictate alignment requirements on a
	//	per-architecture basis. In the absense of that we
	//	take an educated guess.
	#ifdef BOE_PLATFORM_NEW_BLOCK_ALIGNMENT
		size_t alignment = XML_PLATFORM_NEW_BLOCK_ALIGNMENT;
	#else
		size_t alignment = (sizeof(void*) >= sizeof(double)) ? sizeof(void*) : sizeof(double);
	#endif
	
	//	Calculate current alignment of pointer
	size_t current = ptrSize % alignment;
	
	//	Adjust pointer alignment as needed
	return (current == 0)
		 ? ptrSize
		 : (ptrSize + alignment - current);
}
