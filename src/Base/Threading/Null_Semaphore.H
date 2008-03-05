

#ifndef JOMOO_NULL_SEMAPHORE_H
#define JOMOO_NULL_SEMAPHORE_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "config_threading.h"
#include "Guard.h"

_JOMOO_begin

class JOMOO_Null_Semaphore
{
public:

	typedef JOMOO_Guard< JOMOO_Null_Semaphore > spcode_lock;

	JOMOO_Null_Semaphore( long lInitialCount,long lMaxCount,const char* pSemaphoreName=NULL )
	{
		
	}

	~JOMOO_Null_Semaphore()
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
	DECLARE_NO_COPY_CLASS( JOMOO_Null_Semaphore );
};

_JOMOO_end


#endif // JOMOO_NULL_SEMAPHORE_H