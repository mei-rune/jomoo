
#include "os.h"

#ifdef _jomoo_memory_DEBUG
#undef THIS_FILE
#define new	   DEBUG_NEW  
#define malloc DEBUG_MALLOC  
static char THIS_FILE[] = __FILE__;  
#endif // _jomoo_memory_DEBUG

#if !defined (OS_HAS_INLINED)
# include "os.inl"
#endif /* OS_HAS_INLINED */
