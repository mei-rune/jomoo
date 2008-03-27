

#ifndef null_mutex_H
#define null_mutex_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "config_threading.h"
#include "guard.h"

_jomoo_begin

class null_mutex
{
public:
	
	typedef guard< null_mutex > spcode_lock;

	null_mutex()
	{
		
	}

	~null_mutex()
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
	DECLARE_NO_COPY_CLASS( null_mutex );
};

_jomoo_end


#endif // null_mutex_H