

#ifndef null_semaphore_h
#define null_semaphore_h

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "config_threading.h"
#include "guard.h"

_jomoo_begin

class null_semaphore
{
public:

	typedef guard< null_semaphore > spcode_lock;

	null_semaphore( long lInitialCount,long lMaxCount,const char* pSemaphoreName=NULL )
	{
		
	}

	~null_semaphore()
	{
		
	}
	bool acquire( )
	{
		return true;
	}

	void release(long lAmount=1)
	{
	}

#ifdef _WIN32_ADV_
	bool tryacquire(u_long ulMSTimeout= 10000 )
	{
		return true;
	}
#endif


private:
	DECLARE_NO_COPY_CLASS( null_semaphore );
};

_jomoo_end


#endif // null_semaphore_h