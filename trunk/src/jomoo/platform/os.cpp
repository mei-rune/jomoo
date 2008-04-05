
#include "os.h"

#ifdef _MEMORY_DEBUG
#undef THIS_FILE
#define new	   DEBUG_NEW  
#define malloc DEBUG_MALLOC  
static char THIS_FILE[] = __FILE__;  
#endif // _MEMORY_DEBUG

#if !defined (OS_HAS_INLINED)
# include "OS.inl"
#endif /* OS_HAS_INLINED */
