

#ifndef mutex_H
#define mutex_H

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "config_threading.h"

#ifdef JOMOO_MT

#include "guard.h"

_thread_begin

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

_thread_end

#endif // JOMOO_MT

#endif // mutex_H