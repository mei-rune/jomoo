

#ifndef JOMOO_EVENT_H
#define JOMOO_EVENT_H

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "config_threading.h"

#ifdef JOMOO_MT

#include "jomoo/platform/os_string.h"
#include "exception.hpp"

_thread_begin

class jomoo_event
{
public:
	jomoo_event( const tchar* name , bool manualReset, bool initialState )
		: event_handler_( NULL )
		, m_name_( name == 0 ? _T("") : name )
	{
		event_handler_ =CreateEvent(0, manualReset,initialState, 0 );
		if( event_handler_ == NULL )
			if( name != 0 )
				ThrowException1( RuntimeException, _T("创建事件[") + m_name_ + _T("]失败") );
			else
				ThrowException1( RuntimeException, _T("创建事件失败") );
	}

	~jomoo_event(void )
	{
		CloseHandle( event_handler_ );
	}

	/**
	* 等待信号
	*/
	bool wait (void)
	{
		return WaitForSingleObject( event_handler_, INFINITE ) == WAIT_OBJECT_0 ? true : false ;
	}

	bool wait ( int time )
	{
		return WaitForSingleObject( event_handler_, time ) == WAIT_OBJECT_0 ? true : false ;
	}

	bool signal ( )
	{
		return TRUE == SetEvent( event_handler_ );
	}

	bool pulse ( )
	{
		return TRUE == PulseEvent( this->event_handler_ );
	}

	bool reset ( )
	{
		return TRUE == ResetEvent( this->event_handler_ );
	}

	//	JOMOO_HANDLE open_event( u_long DesiredAccess,bool bInheritHandle,const tchar* lpName )
	//  {
	//	  return OpenEvent( DesiredAccess,bInheritHandle,lpName );
	//  }

	//u_long wait_for_singleobjectex(
	//	JOMOO_HANDLE hHandle, 
	//	u_long timeout,
	//	bool bAlertable        // alertable option
	//	)
	//{
	//	return WaitForSingleObjectEx( hHandle,timeout,bAlertable );
	//}
//
//	u_long wait_for_singleobject(
//		JOMOO_HANDLE hHandle,        // handle to object
//		u_long timeout   // time-out interval
//		)
//	{
//		return WaitForSingleObject( hHandle,timeout );
//	}
//
//	u_long wait_for_multipleobjects(
//		const JOMOO_HANDLE* hHandles,
//		size_t n,
//		bool bWaitAll,            // wait option
//		u_long timeout      // time-out interval
//		)
//	{
//		return WaitForMultipleObjects( u_long( n ) ,hHandles ,bWaitAll,timeout );
//	}
//
//	u_long wait_for_multipleobjectsex(
//		const JOMOO_HANDLE* hHandles,
//		size_t n,
//		bool bWaitAll,            // wait option
//		u_long timeout,      // time-out interval
//		bool bAlertable           // alertable option
//		)
//	{
//		return WaitForMultipleObjectsEx( u_long( n ) ,hHandles ,bWaitAll,timeout ,bAlertable );
//	}
//
//#if(_WIN32_WINNT >= 0x0400)
//
//	u_long signal_object_and_wait(
//		JOMOO_HANDLE hObjectToSignal,  // handle to object to signal
//		JOMOO_HANDLE hObjectToWaitOn,  // handle to object to watch
//		u_long timeout,      // time-out interval
//		bool bAlertable          // alertable option
//		)
//	{
//		return SignalObjectAndWait( hObjectToSignal,hObjectToWaitOn,timeout, bAlertable );
//	}
//
//#endif 
private:

	DECLARE_NO_COPY_CLASS( jomoo_event );

	HANDLE event_handler_;
	tstring m_name_;
};

_thread_end

#endif // JOMOO_MT

#endif // JOMOO_EVENT_H
