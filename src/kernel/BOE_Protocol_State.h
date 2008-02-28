// BOE


#ifndef __BOE_PROTOCOL_STATE__
#define __BOE_PROTOCOL_STATE__

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

class BOE_Protocol_State
{

public:

	virtual int service( ) = 0;

	virtual BOE_Protocol_State* transition() = 0;

};// END CLASS DEFINITION BOE_Protocol_State

#endif // __BOE_PROTOCOL_STATE__
