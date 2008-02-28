// BOE


#ifndef __BOE_PROTOCOL_STATE__
#define __BOE_PROTOCOL_STATE__

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

// Include files
#include "config_Kernel.h"

_kernel_begin

class BOE_Protocol_State
{
public:

	virtual ~BOE_Protocol_State() {}

	virtual int service( void *data ) = 0;

	virtual BOE_Protocol_State* transition( void *data ,void* result, void* act ) = 0;

};// END CLASS DEFINITION BOE_Protocol_State

template< typename T, typename R, typename A = void >
class BOE_Protocol_State_T : public BOE_Protocol_State
{
public:

	virtual ~BOE_Protocol_State_T() {}

	int service( void *data )
	{
		if( data == 0 )
			return -1;
		return service( *(T*)data );
	}

	virtual BOE_Protocol_State* transition( void *data ,void* result, void* act )
	{
		if( data == 0 )
			return 0;
		return transition( *(T*)data, *(R*)result, (A*)act );
	}

	virtual int service( T& t ) = 0;
	virtual BOE_Protocol_State* transition( T& data ,R& result, A* act ) = 0;

};// END CLASS DEFINITION BOE_Protocol_State_T

_kernel_end

#endif // __BOE_PROTOCOL_STATE__
