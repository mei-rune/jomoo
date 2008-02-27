

#ifndef _OS_Threading_H
#define _OS_Threading_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

#include "Hazel.Platform/OS.H"

namespace OS
{

	Hazel_NAMESPACE_INLINE_FUNCTION
		Hazel_HANDLE create_semaphore( long lInitialCount,
		long lMaxCount,const char* pSemaphoreName);

	Hazel_NAMESPACE_INLINE_FUNCTION
		bool close_semaphore( Hazel_HANDLE &handle );

	Hazel_NAMESPACE_INLINE_FUNCTION
		bool aquire_semaphore( Hazel_HANDLE &handle, 
		unsigned long timeout );

	Hazel_NAMESPACE_INLINE_FUNCTION
		bool release_semaphore( Hazel_HANDLE &handle, long count );


	Hazel_NAMESPACE_INLINE_FUNCTION
		Hazel_HANDLE create_event(  bool bManualReset
		,bool bInitialState,const char* lpName = 0 );

	Hazel_NAMESPACE_INLINE_FUNCTION
		Hazel_HANDLE open_event( u_long DesiredAccess
		,bool bInheritHandle,const char* lpName = 0 );

	Hazel_NAMESPACE_INLINE_FUNCTION
		bool set_event( Hazel_HANDLE hEvent );

	Hazel_NAMESPACE_INLINE_FUNCTION
		bool reset_event( Hazel_HANDLE hEvent );

	Hazel_NAMESPACE_INLINE_FUNCTION
		bool pulse_event( Hazel_HANDLE hEvent );

	Hazel_NAMESPACE_INLINE_FUNCTION
		u_long wait_for_singleobjectex(
		Hazel_HANDLE hHandle,        // handle to object
		u_long timeout,  // time-out interval
		bool bAlertable        // alertable option
		);

	Hazel_NAMESPACE_INLINE_FUNCTION
		u_long wait_for_singleobject(
		Hazel_HANDLE hHandle,        // handle to object
		u_long timeout   // time-out interval
		);

	Hazel_NAMESPACE_INLINE_FUNCTION
		u_long wait_for_multipleobjects(
		const Hazel_HANDLE* hHandles,
		size_t n,
		bool bWaitAll,            // wait option
		u_long timeout      // time-out interval
		);

	Hazel_NAMESPACE_INLINE_FUNCTION
		u_long wait_for_multipleobjectsex(
		const Hazel_HANDLE* hHandles,
		size_t n,
		bool bWaitAll,            // wait option
		u_long timeout,      // time-out interval
		bool bAlertable           // alertable option
		);
#if(_WIN32_WINNT >= 0x0400)
	Hazel_NAMESPACE_INLINE_FUNCTION
		u_long signal_object_and_wait(
		Hazel_HANDLE hObjectToSignal,  // handle to object to signal
		Hazel_HANDLE hObjectToWaitOn,  // handle to object to watch
		u_long dwMilliseconds,    // time-out interval
		bool bAlertable          // alertable option
		);
#endif 

	Hazel_NAMESPACE_INLINE_FUNCTION
		void create_critical_section( critical_section* section );

	Hazel_NAMESPACE_INLINE_FUNCTION
		void close_critical_section( critical_section* section );

	Hazel_NAMESPACE_INLINE_FUNCTION 
		void enter_critical_section( critical_section* section );

	Hazel_NAMESPACE_INLINE_FUNCTION
		void leave_critical_section( critical_section* section );

#if(_WIN32_WINNT >= 0x0400)
	Hazel_NAMESPACE_INLINE_FUNCTION
		bool try_enter_critical_section( critical_section* section );
#endif

# if defined (OS_HAS_INLINED)
#   include "os_threading.inl"
# endif /* Hazel_HAS_INLINED_OSCALLS */

};





#endif // _OS_Threading_H