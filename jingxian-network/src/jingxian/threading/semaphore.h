

#if !defined _JINGXIAN_THREAD_SEMAPHORE_H_
#define _JINGXIAN_THREAD_SEMAPHORE_H_

#include "jingxian/config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

#ifdef JINGXIAN_MT

// Include files
# include "jingxian/threading/guard.h"

_jingxian_begin

class semaphore
{
public:
	
	typedef guard< semaphore > scoped_lock;

	semaphore(long initialCount,long maxCount,const tchar* name=NULL)
		: m_hSemaphore( NULL ),
		m_delete_( true )
	{
		m_hSemaphore=::CreateSemaphore( NULL, initialCount,maxCount,name );

		if( NULL == m_hSemaphore )
		{
			if( name != 0 )
				ThrowException1( RuntimeException, _T("创建Semaphore[") + tstring( name ) + _T("]失败"));
			else
				ThrowException1( RuntimeException, _T("创建Semaphore失败"));
		}

		if ( name && GetLastError()==ERROR_ALREADY_EXISTS)
			m_delete_=false;
	}

	~semaphore()
	{
		if ( m_delete_ )
			CloseHandle( m_hSemaphore );
	}

	bool acquire( )
	{
		return WAIT_TIMEOUT != WaitForSingleObject( m_hSemaphore,INFINITE );
	}

	void release(long lAmount=1)
	{
		ReleaseSemaphore( m_hSemaphore,lAmount, 0 );
	}

#if(_WIN32_WINNT >= 0x0400)
	bool tryacquire(u_long ulMSTimeout= 10000 )
	{
		return WAIT_TIMEOUT != WaitForSingleObject( m_hSemaphore,ulMSTimeout );
	}
#endif

private:
	DECLARE_NO_COPY_CLASS( semaphore );

	HANDLE m_hSemaphore;
	bool m_delete_;
};

_jingxian_end

#endif // JINGXIAN_MT

#endif // !defined(_JINGXIAN_THREAD_SEMAPHORE_H_)
