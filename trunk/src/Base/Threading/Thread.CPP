

#ifndef JOMOO_THREAD_CPP
#define JOMOO_THREAD_CPP


#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "config_threading.h"

#ifdef JOMOO_MT

JOMOO_Export_C _thread JOMOO_Thread* ___get_JOMOO_Thread( )
{
	return 0;
}

_thread_begin



#ifndef OS_HAS_INLINED

void JOMOO_Thread::static_thread_svc( void * arg )
{
	try{
	JOMOO_Thread* thread_ = ( JOMOO_Thread* ) arg;
	thread_->m_runfn_.run();
	_endthreadex( 0 );
	return ;
	}
	catch( ... )
	{
	}
	_endthreadex( -1 );
}

#include "JOMOO_Thread.inl"

#endif // OS_HAS_INLINED


_thread_end

#endif // JOMOO_MT

#endif /* JOMOO_THREAD_CPP */
