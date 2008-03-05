

#ifndef JOMOO_NULL_MUTEX_H
#define JOMOO_NULL_MUTEX_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "config_threading.h"
#include "Guard.h"

_JOMOO_begin

class JOMOO_Null_Mutex
{
public:
	typedef JOMOO_Guard< JOMOO_Null_Mutex > spcode_lock;
	JOMOO_Null_Mutex()
	{
		
	}

	~JOMOO_Null_Mutex()
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
	DECLARE_NO_COPY_CLASS( JOMOO_Null_Mutex );
};

_JOMOO_end


#endif // JOMOO_NULL_MUTEX_H