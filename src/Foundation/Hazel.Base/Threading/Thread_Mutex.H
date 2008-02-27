

#ifndef Hazel_THREAD_MUTEX_H
#define Hazel_THREAD_MUTEX_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

#include "config_threading.h"

#ifdef Hazel_MT

#include "os_threading.h"
#include "Hazel_Guard.h"

_hazel_begin

class Hazel_Thread_Mutex
{
private:
	critical_section section_;
public:
	typedef Hazel_Guard< Hazel_Thread_Mutex > spcode_lock;
	Hazel_Thread_Mutex()
	{
		OS::create_critical_section( &section_ );
	}

	~Hazel_Thread_Mutex()
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
	DECLARE_NO_COPY_CLASS( Hazel_Thread_Mutex );
};

_hazel_end

#endif // Hazel_MT

#endif // Hazel_THREAD_MUTEX_H