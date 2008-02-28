

#ifndef Hazel_NULL_SEMAPHORE_H
#define Hazel_NULL_SEMAPHORE_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

#include "config_threading.h"
#include "Guard.h"

_hazel_begin

class Hazel_Null_Semaphore
{
public:

	typedef Hazel_Guard< Hazel_Null_Semaphore > spcode_lock;

	Hazel_Null_Semaphore( long lInitialCount,long lMaxCount,const char* pSemaphoreName=NULL )
	{
		
	}

	~Hazel_Null_Semaphore()
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
	DECLARE_NO_COPY_CLASS( Hazel_Null_Semaphore );
};

_hazel_end


#endif // Hazel_NULL_SEMAPHORE_H