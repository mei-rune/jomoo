

#if !defined _JOMOO_THREAD_SEMAPHORE_H_
#define _JOMOO_THREAD_SEMAPHORE_H_

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "config_threading.h"

#ifdef JOMOO_MT

#include "os_threading.h"
#include "guard.h"

_jomoo_begin

class thread_semaphore
{
public:
	
	typedef guard< thread_semaphore > scoped_lock;

	thread_semaphore(long initialCount,long maxCount,const char* name=NULL)
		: m_hSemaphore( NULL ),
		m_delete_( true )
	{
		m_hSemaphore=OS::create_semaphore( initialCount,maxCount,name);

		if( NULL == m_hSemaphore )
		{
			if( name != 0 )
				ThrowException1( RuntimeException, BT_TEXT("创建Semaphore[") + tstring( name ) + BT_TEXT("]失败") );
			else
				ThrowException1( RuntimeException, BT_TEXT("创建Semaphore失败") );
		}

		if ( name && GetLastError()==ERROR_ALREADY_EXISTS)
			m_delete_=false;
	}

	~thread_semaphore()
	{
		if ( m_delete_ )
			OS::close_semaphore( m_hSemaphore );
	}

	bool acquire( )
	{
		return OS::aquire_semaphore( m_hSemaphore,INFINITE );
	}

	void release(long lAmount=1)
	{
		OS::release_semaphore( m_hSemaphore,lAmount );
	}

#if(_WIN32_WINNT >= 0x0400)
	bool tryacquire(u_long ulMSTimeout= 10000 )
	{
		return OS::aquire_semaphore( m_hSemaphore,ulMSTimeout );
	}
#endif

private:
	DECLARE_NO_COPY_CLASS( thread_semaphore );

	JOMOO_HANDLE m_hSemaphore;
	bool m_delete_;
};

_jomoo_end

#endif // JOMOO_MT

#endif // !defined(_JOMOO_THREAD_SEMAPHORE_H_)
