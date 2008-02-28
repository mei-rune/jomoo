// BOE


#ifndef __BOE_PROTOCOL_HANDLER__
#define __BOE_PROTOCOL_HANDLER__

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

// Include files
#include "config_Kernel.h"
#include "BOE/counter_ptr.hpp"

_kernel_begin

class BOE_Protocol_Handler : virtual public BOEShared
{
public:
	typedef intrusive_ptr<BOE_Protocol_Handler> ptr_type;

	virtual ~BOE_Protocol_Handler(){}

	virtual void finalize() = 0;

	virtual int service() = 0;

};// END CLASS DEFINITION BOE_Protocol_Handler


typedef BOE_Protocol_Handler::ptr_type BOE_Protocol_Handler_Ptr;

_kernel_end

#endif // __BOE_PROTOCOL_HANDLER__
