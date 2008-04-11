

#ifndef JOMOO_THREAD_H
#define JOMOO_THREAD_H


#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "config_threading.h"
#include <process.h>
#include "thread_closure.h"

#ifdef JOMOO_MT

_thread_begin
	
typedef uintptr_t thread_t;

	inline void yield()
	{
		::Sleep( 0 );
	}

	inline void sleep(int millis, int nanaos = 0)
	{
		::Sleep( millis );
	}

	inline void join_thread( thread_t t )
	{
		::WaitForSingleObject(reinterpret_cast<HANDLE>(t), INFINITE);
	}

	template<typename F>
	inline thread_t create_thread( const F& f, const tchar* nm = 0)
	{
		typedef thread_closure_0<F> closure_type;

		pool_ptr pl = getPool();

		return ::_beginthread( closure_type::start_routine, 0, JOMOO_NEW( pl, closure_type, (pl, f, nm) ) );
	}

	template<typename F, typename P>
	inline thread_t create_thread( const F& f, const P& x, const tchar* nm)
	{
		typedef thread_closure_1<F,P> closure_type;

		pool_ptr pl = getPool();
		
		return ::_beginthread( closure_type::start_routine, 0, JOMOO_NEW( pl, closure_type, (pl, f, x, nm) ) );
	}
	
	template<typename F, typename P1, typename P2>
	inline thread_t create_thread( const F& f, const P1& x1, const P2& x2, const tchar* nm)
	{
		typedef thread_closure_2<F,P1,P2> closure_type;

		pool_ptr pl = getPool();
		return ::_beginthread( closure_type::start_routine, 0, JOMOO_NEW( pl, closure_type, (pl, f, x1, x2, nm) ) );
	}

	template<typename F, typename P1, typename P2, typename P3>
	inline thread_t create_thread( const F& f, const P1& x1, const P2& x2, const P3& x3, const tchar* nm )
	{
		typedef thread_closure_3<F,P1,P2,P3> closure_type;

		pool_ptr pl = getPool();
		return ::_beginthread( closure_type::start_routine, 0, JOMOO_NEW( pl, closure_type, (pl, f, x1, x2, x3, nm) ) );
	}

_thread_end

#endif // JOMOO_MT

#endif /* JOMOO_THREAD_H */
