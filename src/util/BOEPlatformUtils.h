
#if !defined(BOEPLATFORMUTILS_H)
#define BOEPLATFORMUTILS_H

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include "util/BT_Memory_Base.H"

class BOEPlatformUtils
{
public:

	static  _bt BT_Memory_Base* fgMemoryManager;

	static size_t alignPointerForNewBlockAllocation ( size_t ptrSize );

};

#endif // 