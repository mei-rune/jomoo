
#include "os_mmap.h"

#ifdef _MEMORY_DEBUG
#undef THIS_FILE
#define new	   DEBUG_NEW  
#define malloc DEBUG_MALLOC  
static char THIS_FILE[] = __FILE__;  
#endif // _MEMORY_DEBUG

#if !defined (OS_HAS_INLINED)
# include "OS_mmap.inl"
#endif /* JOMOO_HAS_INLINED_OS_CALLS */


namespace OS
{

};