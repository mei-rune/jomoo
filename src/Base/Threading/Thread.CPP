

#ifndef Hazel_THREAD_CPP
#define Hazel_THREAD_CPP


#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

#include "config_threading.h"

#ifdef Hazel_MT

BT_Export_C _thread Hazel_Thread* ___get_Hazel_Thread( )
{
	return 0;
}

_thread_begin



#ifndef OS_HAS_INLINED

void Hazel_Thread::static_thread_svc( void * arg )
{
	try{
	Hazel_Thread* thread_ = ( Hazel_Thread* ) arg;
	thread_->m_runfn_.run();
	_endthreadex( 0 );
	return ;
	}
	catch( ... )
	{
	}
	_endthreadex( -1 );
}

#include "Hazel_Thread.inl"

#endif // OS_HAS_INLINED


_thread_end

#endif // Hazel_MT

#endif /* Hazel_THREAD_CPP */
