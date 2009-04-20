

#ifndef null_semaphore_h
#define null_semaphore_h

#include "jingxian/config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include "jingxian/threading/guard.h"

_jingxian_begin

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

_jingxian_end


#endif // null_semaphore_h