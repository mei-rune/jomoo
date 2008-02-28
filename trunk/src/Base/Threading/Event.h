

#ifndef Hazel_EVENT_H
#define Hazel_EVENT_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

#include "config_threading.h"

#ifdef Hazel_MT

#include "os_threading.h"
#include "Hazel.Base/string.hpp"
#include "Hazel.Base/exception.hpp"
_hazel_begin

class Hazel_Event
{
public:
	Hazel_Event( const tchar* name , bool ManualReset, bool InitialState )
		: event_handler_( NULL )
		, m_name_( name == 0 ? BT_TEXT("") : name )
	{
		event_handler_ = OS::create_event( ManualReset,InitialState );
		if( event_handler_ == NULL )
			if( name != 0 )
				ThrowException1( RuntimeException, BT_TEXT("创建事件[") + m_name_ + BT_TEXT("]失败") );
			else
				ThrowException1( RuntimeException, BT_TEXT("创建事件失败") );
	}

	~Hazel_Event(void )
	{
		OS::close_handle( event_handler_ );
	}

	/**
	* 等待信号
	*/
	bool wait (void)
	{
		return OS::wait_for_singleobject( event_handler_, INFINITE ) == WAIT_OBJECT_0 ? true : false ;
	}

	int wait ( int time )
	{
		return OS::wait_for_singleobject( event_handler_, time * 1000 ) == WAIT_OBJECT_0 ? true : false ;
	}

	bool signal ( )
	{
		return OS::set_event( event_handler_ );
	}

	bool pulse ( )
	{
		return OS::pulse_event( this->event_handler_ );
	}

	bool reset ( )
	{
		return OS::reset_event( this->event_handler_ );
	}

private:

	DECLARE_NO_COPY_CLASS( Hazel_Event );

	Hazel_HANDLE event_handler_;
	tstring m_name_;
};

_hazel_end

#endif // Hazel_MT

#endif // Hazel_EVENT_H
