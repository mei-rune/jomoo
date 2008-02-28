// BOE


#ifndef __BOE_PROTOCOL_HANDLER__
#define __BOE_PROTOCOL_HANDLER__

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

class BOE_Protocol_Handler
{

public:

	virtual void dismiss() = 0;

	virtual int service() = 0;

};// END CLASS DEFINITION BOE_Protocol_Handler

#endif // __BOE_PROTOCOL_HANDLER__
