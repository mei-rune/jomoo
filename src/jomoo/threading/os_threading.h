

#ifndef _OS_Threading_H
#define _OS_Threading_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "Platform/OS.H"

namespace OS
{

	OS_INLINED
		JOMOO_HANDLE create_semaphore( long lInitialCount,
		long lMaxCount,const char* pSemaphoreName);

	OS_INLINED
		bool close_semaphore( JOMOO_HANDLE &handle );

	OS_INLINED
		bool aquire_semaphore( JOMOO_HANDLE &handle, 
		unsigned long timeout );

	OS_INLINED
		bool release_semaphore( JOMOO_HANDLE &handle, long count );


	OS_INLINED
		JOMOO_HANDLE create_event(  bool bManualReset
		,bool bInitialState,const char* lpName = 0 );

	OS_INLINED
		JOMOO_HANDLE open_event( u_long DesiredAccess
		,bool bInheritHandle,const char* lpName = 0 );

	OS_INLINED
		bool set_event( JOMOO_HANDLE hEvent );

	OS_INLINED
		bool reset_event( JOMOO_HANDLE hEvent );

	OS_INLINED
		bool pulse_event( JOMOO_HANDLE hEvent );

	OS_INLINED
		u_long wait_for_singleobjectex(
		JOMOO_HANDLE hHandle,        // handle to object
		u_long timeout,  // time-out interval
		bool bAlertable        // alertable option
		);

	OS_INLINED
		u_long wait_for_singleobject(
		JOMOO_HANDLE hHandle,        // handle to object
		u_long timeout   // time-out interval
		);

	OS_INLINED
		u_long wait_for_multipleobjects(
		const JOMOO_HANDLE* hHandles,
		size_t n,
		bool bWaitAll,            // wait option
		u_long timeout      // time-out interval
		);

	OS_INLINED
		u_long wait_for_multipleobjectsex(
		const JOMOO_HANDLE* hHandles,
		size_t n,
		bool bWaitAll,            // wait option
		u_long timeout,      // time-out interval
		bool bAlertable           // alertable option
		);
#if(_WIN32_WINNT >= 0x0400)
	OS_INLINED
		u_long signal_object_and_wait(
		JOMOO_HANDLE hObjectToSignal,  // handle to object to signal
		JOMOO_HANDLE hObjectToWaitOn,  // handle to object to watch
		u_long dwMilliseconds,    // time-out interval
		bool bAlertable          // alertable option
		);
#endif 

	OS_INLINED
		void create_critical_section( critical_section* section );

	OS_INLINED
		void close_critical_section( critical_section* section );

	OS_INLINED 
		void enter_critical_section( critical_section* section );

	OS_INLINED
		void leave_critical_section( critical_section* section );

#if(_WIN32_WINNT >= 0x0400)
	OS_INLINED
		bool try_enter_critical_section( critical_section* section );
#endif

# if defined (OS_HAS_INLINED)
#   include "os_threading.inl"
# endif /* OS_HAS_INLINED */

};

#endif // _OS_Threading_H