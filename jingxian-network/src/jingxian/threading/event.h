

#ifndef JINGXIAN_EVENT_H
#define JINGXIAN_EVENT_H

#include "jingxian/config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */


#ifdef JINGXIAN_MT

// Include files
# include "jingxian/string/string.hpp"
# include "jingxian/exception.hpp"

_jingxian_begin

class jingxian_event
{
public:
	jingxian_event( const tchar* name , bool manualReset, bool initialState )
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

	~jingxian_event(void )
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

	//	JINGXIAN_HANDLE open_event( u_long DesiredAccess,bool bInheritHandle,const tchar* lpName )
	//  {
	//	  return OpenEvent( DesiredAccess,bInheritHandle,lpName );
	//  }

	//u_long wait_for_singleobjectex(
	//	JINGXIAN_HANDLE hHandle, 
	//	u_long timeout,
	//	bool bAlertable        // alertable option
	//	)
	//{
	//	return WaitForSingleObjectEx( hHandle,timeout,bAlertable );
	//}
	//
	//	u_long wait_for_singleobject(
	//		JINGXIAN_HANDLE hHandle,        // handle to object
	//		u_long timeout   // time-out interval
	//		)
	//	{
	//		return WaitForSingleObject( hHandle,timeout );
	//	}
	//
	//	u_long wait_for_multipleobjects(
	//		const JINGXIAN_HANDLE* hHandles,
	//		size_t n,
	//		bool bWaitAll,            // wait option
	//		u_long timeout      // time-out interval
	//		)
	//	{
	//		return WaitForMultipleObjects( u_long( n ) ,hHandles ,bWaitAll,timeout );
	//	}
	//
	//	u_long wait_for_multipleobjectsex(
	//		const JINGXIAN_HANDLE* hHandles,
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
	//		JINGXIAN_HANDLE hObjectToSignal,  // handle to object to signal
	//		JINGXIAN_HANDLE hObjectToWaitOn,  // handle to object to watch
	//		u_long timeout,      // time-out interval
	//		bool bAlertable          // alertable option
	//		)
	//	{
	//		return SignalObjectAndWait( hObjectToSignal,hObjectToWaitOn,timeout, bAlertable );
	//	}
	//
	//#endif 
private:

	DECLARE_NO_COPY_CLASS( jingxian_event );

	HANDLE event_handler_;
	tstring m_name_;
};

_jingxian_end

#endif // JINGXIAN_MT

#endif // JINGXIAN_EVENT_H
