

#if !defined _Hazel_THREAD_SEMAPHORE_H_
#define _Hazel_THREAD_SEMAPHORE_H_

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

#include "config_threading.h"

#ifdef Hazel_MT

#include "os_threading.h"
#include "Hazel_Guard.h"

_hazel_begin

class Hazel_Thread_Semaphore
{
public:
	typedef Hazel_Guard< Hazel_Thread_Semaphore > scoped_lock;

	bool acquire( )
	{
		return OS::aquire_semaphore( m_hSemaphore,INFINITE );
	}

	void release(long lAmount=1)
	{
		OS::release_semaphore( m_hSemaphore,lAmount );
	}

#ifdef _WIN32_ADV_
	bool tryacquire(u_long ulMSTimeout= 10000 )
	{
		return OS::aquire_semaphore( m_hSemaphore,ulMSTimeout );
	}
#endif

	Hazel_Thread_Semaphore(long lInitialCount,long lMaxCount,const char* pSemaphoreName=NULL)
		: m_hSemaphore( NULL ),
		m_delete_( true )
	{
		m_hSemaphore=OS::create_semaphore( lInitialCount,lMaxCount,pSemaphoreName);
		if ( pSemaphoreName && GetLastError()==ERROR_ALREADY_EXISTS)
			m_delete_=false;
		else if( pSemaphoreName == NULL )
		{
			//if( pSemaphoreName != 0 )
			//	ThrowException1( RuntimeException, BT_TEXT("创建Semaphore[") + m_name_ + BT_TEXT("]失败") );
			//else
				ThrowException1( RuntimeException, BT_TEXT("创建Semaphore失败") );
		}
		

	}
	~Hazel_Thread_Semaphore()
	{
		if ( m_delete_ )
			OS::close_semaphore( m_hSemaphore );
	}
private:
	DECLARE_NO_COPY_CLASS( Hazel_Thread_Semaphore );

	Hazel_HANDLE m_hSemaphore;
	bool m_delete_;
};

_hazel_end

#endif // Hazel_MT

#endif // !defined(_Hazel_THREAD_SEMAPHORE_H_)
