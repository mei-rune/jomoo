// BOE


#ifndef __BOE_DISPATCHER__
#define __BOE_DISPATCHER__

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

// Include files
#include "config_Kernel.h"
#include "BOE_Protocol_Handler.h"

_kernel_begin

class BOE_Dispatcher
{

public:

	int putq( BOE_Protocol_Handler* ph );

	int getq( BOE_Protocol_Handler*& ph );

};// END CLASS DEFINITION BOE_Dispatcher

_kernel_end

#endif // __BOE_DISPATCHER__
