

#include "BOE_Concurrency.h"
#include "BOE_NULL_Concurrency.h"
#include "BOE_Protocol_Handler.h"

#ifdef _MEMORY_DEBUG
#undef THIS_FILE
#define new	   DEBUG_NEW  
#define malloc DEBUG_MALLOC  
static char THIS_FILE[] = __FILE__;  
#endif // _MEMORY_DEBUG


BOE_NULL_Concurrency::BOE_NULL_Concurrency ( )
  : BOE_Concurrency_Impl( ) 
{
}

int BOE_NULL_Concurrency::putq (BOE_Protocol_Handler_Ptr ph)
{
	if( isNone( ph ) )
		return -1;
	return ph->service();
}

int BOE_NULL_Concurrency::getq (BOE_Protocol_Handler_Ptr &ph)
{
	return -1;
}

void BOE_NULL_Concurrency::run (void)
{
}