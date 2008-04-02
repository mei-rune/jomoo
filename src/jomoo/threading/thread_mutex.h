

#ifndef mutex_H
#define mutex_H

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "config_threading.h"

#ifdef JOMOO_MT

#include "os_threading.h"
#include "guard.h"

_jomoo_begin

class thread_mutex
{
public:
	
	typedef guard< thread_mutex > spcode_lock;

	thread_mutex()
	{
		OS::create_critical_section( &section_ );
	}

	~thread_mutex()
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

	DECLARE_NO_COPY_CLASS( thread_mutex );

	critical_section section_;
};

_jomoo_end

#endif // JOMOO_MT

#endif // mutex_H