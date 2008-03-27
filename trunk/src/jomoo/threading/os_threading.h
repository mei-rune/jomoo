

#ifndef _OS_Threading_H
#define _OS_Threading_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "Platform/OS.H"

namespace OS
{

	JOMOO_NAMESPACE_INLINE_FUNCTION
		JOMOO_HANDLE create_semaphore( long lInitialCount,
		long lMaxCount,const char* pSemaphoreName);

	JOMOO_NAMESPACE_INLINE_FUNCTION
		bool close_semaphore( JOMOO_HANDLE &handle );

	JOMOO_NAMESPACE_INLINE_FUNCTION
		bool aquire_semaphore( JOMOO_HANDLE &handle, 
		unsigned long timeout );

	JOMOO_NAMESPACE_INLINE_FUNCTION
		bool release_semaphore( JOMOO_HANDLE &handle, long count );


	JOMOO_NAMESPACE_INLINE_FUNCTION
		JOMOO_HANDLE create_event(  bool bManualReset
		,bool bInitialState,const char* lpName = 0 );

	JOMOO_NAMESPACE_INLINE_FUNCTION
		JOMOO_HANDLE open_event( u_long DesiredAccess
		,bool bInheritHandle,const char* lpName = 0 );

	JOMOO_NAMESPACE_INLINE_FUNCTION
		bool set_event( JOMOO_HANDLE hEvent );

	JOMOO_NAMESPACE_INLINE_FUNCTION
		bool reset_event( JOMOO_HANDLE hEvent );

	JOMOO_NAMESPACE_INLINE_FUNCTION
		bool pulse_event( JOMOO_HANDLE hEvent );

	JOMOO_NAMESPACE_INLINE_FUNCTION
		u_long wait_for_singleobjectex(
		JOMOO_HANDLE hHandle,        // handle to object
		u_long timeout,  // time-out interval
		bool bAlertable        // alertable option
		);

	JOMOO_NAMESPACE_INLINE_FUNCTION
		u_long wait_for_singleobject(
		JOMOO_HANDLE hHandle,        // handle to object
		u_long timeout   // time-out interval
		);

	JOMOO_NAMESPACE_INLINE_FUNCTION
		u_long wait_for_multipleobjects(
		const JOMOO_HANDLE* hHandles,
		size_t n,
		bool bWaitAll,            // wait option
		u_long timeout      // time-out interval
		);

	JOMOO_NAMESPACE_INLINE_FUNCTION
		u_long wait_for_multipleobjectsex(
		const JOMOO_HANDLE* hHandles,
		size_t n,
		bool bWaitAll,            // wait option
		u_long timeout,      // time-out interval
		bool bAlertable           // alertable option
		);
#if(_WIN32_WINNT >= 0x0400)
	JOMOO_NAMESPACE_INLINE_FUNCTION
		u_long signal_object_and_wait(
		JOMOO_HANDLE hObjectToSignal,  // handle to object to signal
		JOMOO_HANDLE hObjectToWaitOn,  // handle to object to watch
		u_long dwMilliseconds,    // time-out interval
		bool bAlertable          // alertable option
		);
#endif 

	JOMOO_NAMESPACE_INLINE_FUNCTION
		void create_critical_section( critical_section* section );

	JOMOO_NAMESPACE_INLINE_FUNCTION
		void close_critical_section( critical_section* section );

	JOMOO_NAMESPACE_INLINE_FUNCTION 
		void enter_critical_section( critical_section* section );

	JOMOO_NAMESPACE_INLINE_FUNCTION
		void leave_critical_section( critical_section* section );

#if(_WIN32_WINNT >= 0x0400)
	JOMOO_NAMESPACE_INLINE_FUNCTION
		bool try_enter_critical_section( critical_section* section );
#endif

# if defined (OS_HAS_INLINED)
#   include "os_threading.inl"
# endif /* JOMOO_HAS_INLINED_OSCALLS */

};





#endif // _OS_Threading_H