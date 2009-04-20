

#ifndef mutex_H
#define mutex_H

#include "jingxian/config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */


#ifdef JINGXIAN_MT

// Include files
# include "jingxian/threading/guard.h"

_jingxian_begin

class mutex
{
public:
	
	typedef guard< mutex > spcode_lock;

	mutex()
	{
		InitializeCriticalSection( &section_ );
	}

	~mutex()
	{
		DeleteCriticalSection( &section_ );
	}

	bool acquire()
	{
		EnterCriticalSection( &section_ );
		return true;
	}
	void release()
	{
		LeaveCriticalSection( &section_ );
	}

#if(_WIN32_WINNT >= 0x0400)
	bool tryacquire()
	{
		return TryEnterCriticalSection( &section_ );
	}
#endif

private:

	DECLARE_NO_COPY_CLASS( mutex );

	CRITICAL_SECTION section_;
};

_jingxian_end

#endif // JINGXIAN_MT

#endif // mutex_H