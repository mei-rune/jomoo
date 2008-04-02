

#ifndef _OS_Threading_H
#define _OS_Threading_H

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "Platform/OS.H"

namespace OS
{


	OS_INLINE
		JOMOO_HANDLE create_semaphore( long lInitialCount,
		long lMaxCount,const char* pSemaphoreName);


	OS_INLINE
		bool close_semaphore( JOMOO_HANDLE &handle );

	OS_INLINE
		bool aquire_semaphore( JOMOO_HANDLE &handle, 
		unsigned long timeout );

	OS_INLINE
		bool release_semaphore( JOMOO_HANDLE &handle, long count );

	OS_INLINE
		JOMOO_HANDLE create_event(  bool bManualReset
		,bool bInitialState,const char* lpName = 0 );

	OS_INLINE
		JOMOO_HANDLE open_event( u_long DesiredAccess
		,bool bInheritHandle,const char* lpName = 0 );

	OS_INLINE
		bool set_event( JOMOO_HANDLE hEvent );

	OS_INLINE
		bool reset_event( JOMOO_HANDLE hEvent );

	OS_INLINE
		bool pulse_event( JOMOO_HANDLE hEvent );

	OS_INLINE
		u_long wait_for_singleobjectex(
		JOMOO_HANDLE hHandle,        // handle to object
		u_long timeout,  // time-out interval
		bool bAlertable        // alertable option
		);

	OS_INLINE
		u_long wait_for_singleobject(
		JOMOO_HANDLE hHandle,        // handle to object
		u_long timeout   // time-out interval
		);

	OS_INLINE
		u_long wait_for_multipleobjects(
		const JOMOO_HANDLE* hHandles,
		size_t n,
		bool bWaitAll,            // wait option
		u_long timeout      // time-out interval
		);

	OS_INLINE
		u_long wait_for_multipleobjectsex(
		const JOMOO_HANDLE* hHandles,
		size_t n,
		bool bWaitAll,            // wait option
		u_long timeout,      // time-out interval
		bool bAlertable           // alertable option
		);
#if(_WIN32_WINNT >= 0x0400)

	OS_INLINE
		u_long signal_object_and_wait(
		JOMOO_HANDLE hObjectToSignal,  // handle to object to signal
		JOMOO_HANDLE hObjectToWaitOn,  // handle to object to watch
		u_long dwMilliseconds,    // time-out interval
		bool bAlertable          // alertable option
		);
#endif 

	OS_INLINE
		void create_critical_section( critical_section* section );

	OS_INLINE
		void close_critical_section( critical_section* section );

	OS_INLINE 
		void enter_critical_section( critical_section* section );

	OS_INLINE
		void leave_critical_section( critical_section* section );

#if(_WIN32_WINNT >= 0x0400)
	OS_INLINE
		bool try_enter_critical_section( critical_section* section );
#endif

# if defined (OS_HAS_INLINED)
#   include "os_threading.inl"
# endif /* OS_HAS_INLINED */

};

#endif // _OS_Threading_H