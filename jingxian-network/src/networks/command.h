
#ifndef COMMAND_H
#define COMMAND_H

#include "config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
#include "os_networks.h"

_jingxian_begin

class command : public OVERLAPPED
{
public:

	command( )
		: handle_( INVALID_HANDLE_VALUE )
		//, instance_( 0 )
	{
		Internal =  0;
		InternalHigh =  0;
		Offset =  0;
		OffsetHigh =  0;
		hEvent = 0;
	}

	virtual ~command(void)
	{
	}

	HANDLE handle() const
	{
		return handle_;
	}

    virtual bool bind( void* connection ) = 0;
	virtual bool post() = 0;
	virtual void on_complete (size_t bytes_transferred,
                         int success,
                         const void *completion_key,
                         u_long error = 0) = 0;

protected:
	HANDLE handle_;
};

_jingxian_end

#endif //COMMAND_H