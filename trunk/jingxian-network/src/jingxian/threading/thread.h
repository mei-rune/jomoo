

#ifndef JINGXIAN_THREAD_H
#define JINGXIAN_THREAD_H


#include "jingxian/config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

#ifdef JINGXIAN_MT

// Include files
# include <process.h>
# include "jingxian/threading/thread_closure.h"

_jingxian_begin

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
inline void create_thread( const F& f, const tchar* nm = 0)
{
	typedef thread_closure_0<F> closure_type;

	// _beginthread�����߳�ʱ���䷵��ֵ������һ����Ч���(̫������ر���)��ǧ��Ҫ��������
	// ������ WaitForSingleObject ��,���������
	uintptr_t handle = ::_beginthread( closure_type::start_routine, 0, new closure_type( f, nm) );
	if( -1L == handle )
	{
		if( name != 0 )
			ThrowException1( RuntimeException, _T("�����߳�[") + tstring( nm ) + _T("]ʧ��"));
		else
			ThrowException1( RuntimeException, _T("�����߳�ʧ��"));
	}
}

template<typename F, typename P>
inline void create_thread( const F& f, const P& x, const tchar* nm)
{
	typedef thread_closure_1<F,P> closure_type;

	// _beginthread�����߳�ʱ���䷵��ֵ������һ����Ч���(̫������ر���)��ǧ��Ҫ��������
	// ������ WaitForSingleObject ��,���������
	uintptr_t handle = ::_beginthread( closure_type::start_routine, 0, new closure_type( f, x, nm) );
	if( -1L == handle )
	{
		if( name != 0 )
			ThrowException1( RuntimeException, _T("�����߳�[") + tstring( nm ) + _T("]ʧ��"));
		else
			ThrowException1( RuntimeException, _T("�����߳�ʧ��"));
	}
}

template<typename F, typename P1, typename P2>
inline void create_thread( const F& f, const P1& x1, const P2& x2, const tchar* nm)
{
	typedef thread_closure_2<F,P1,P2> closure_type;

	// _beginthread�����߳�ʱ���䷵��ֵ������һ����Ч���(̫������ر���)��ǧ��Ҫ��������
	// ������ WaitForSingleObject ��,���������
	uintptr_t handle = ::_beginthread( closure_type::start_routine, 0, new closure_type( f, x1, x2, nm)  );
	if( -1L == handle )
	{
		if( name != 0 )
			ThrowException1( RuntimeException, _T("�����߳�[") + tstring( nm ) + _T("]ʧ��"));
		else
			ThrowException1( RuntimeException, _T("�����߳�ʧ��"));
	}
}

template<typename F, typename P1, typename P2, typename P3>
inline void create_thread( const F& f, const P1& x1, const P2& x2, const P3& x3, const tchar* nm )
{
	typedef thread_closure_3<F,P1,P2,P3> closure_type;

	// _beginthread�����߳�ʱ���䷵��ֵ������һ����Ч���(̫������ر���)��ǧ��Ҫ��������
	// ������ WaitForSingleObject ��,���������
	uintptr_t handle = ::_beginthread( closure_type::start_routine, 0, new closure_type( f, x1, x2, x3, nm) );
	if( -1L == handle )
	{
		if( name != 0 )
			ThrowException1( RuntimeException, _T("�����߳�[") + tstring( nm ) + _T("]ʧ��"));
		else
			ThrowException1( RuntimeException, _T("�����߳�ʧ��"));
	}
}

_jingxian_end

#endif // JINGXIAN_MT

#endif /* JINGXIAN_THREAD_H */
