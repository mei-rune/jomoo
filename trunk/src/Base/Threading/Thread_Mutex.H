

#ifndef JOMOO_THREAD_MUTEX_H
#define JOMOO_THREAD_MUTEX_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "config_threading.h"

#ifdef JOMOO_MT

#include "os_threading.h"
#include "JOMOO_Guard.h"

_JOMOO_begin

class JOMOO_Thread_Mutex
{
private:
	critical_section section_;
public:
	typedef JOMOO_Guard< JOMOO_Thread_Mutex > spcode_lock;
	JOMOO_Thread_Mutex()
	{
		OS::create_critical_section( &section_ );
	}

	~JOMOO_Thread_Mutex()
	{
		OS::close_critical_section( &section_ );
	}

	bool acquire()
	{
		OS::enter_critical_section( &section_ );
		return true;
	}
	void release()
	{
		OS::leave_critical_section( &section_ );
	}

#if(_WIN32_WINNT >= 0x0400)
	bool tryacquire()
	{
		return OS::try_enter_critical_section( &section_ );
	}
#endif

private:
	DECLARE_NO_COPY_CLASS( JOMOO_Thread_Mutex );
};

_JOMOO_end

#endif // JOMOO_MT

#endif // JOMOO_THREAD_MUTEX_H