

#ifndef Hazel_NULL_MUTEX_H
#define Hazel_NULL_MUTEX_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

#include "config_threading.h"
#include "Guard.h"

_hazel_begin

class Hazel_Null_Mutex
{
public:
	typedef Hazel_Guard< Hazel_Null_Mutex > spcode_lock;
	Hazel_Null_Mutex()
	{
		
	}

	~Hazel_Null_Mutex()
	{
		
	}

	bool acquire()
	{
		return true;
	}
	void release()
	{
	}

#if(_WIN32_WINNT >= 0x0400)
	bool tryacquire()
	{
		return true;
	}
#endif

private:
	DECLARE_NO_COPY_CLASS( Hazel_Null_Mutex );
};

_hazel_end


#endif // Hazel_NULL_MUTEX_H