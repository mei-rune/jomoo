
#ifndef HAZEL_WIN32_OPERATION_OVERLAPPED_H
#define HAZEL_WIN32_OPERATION_OVERLAPPED_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "config_Networks.h"
#include "include/Hazel_Operation_Result.h"
#include "WIN32OperationProactor.h"
#include <vector>

_networks_begin

class WIN32_Operation_Result
	: public Hazel_OVERLAPPED
	, public Hazel_Operation_Result
{
public:

	WIN32_Operation_Result( )
		: instance_( 0 )
		, m_handle_( HAZEL_INVALID_HANDLE_VALUE )
		, handler_( 0 )
	{
		Internal =  0;
		InternalHigh =  0;
		Offset =  0;
		OffsetHigh =  0;
		hEvent = 0;
	}

	virtual ~WIN32_Operation_Result(void)
	{
	}

	void init( WIN32_Operation_Proactor* instance , Hazel_HANDLE handle )
	{
		if( instance == 0 )
			ThrowException1( NullException, BT_TEXT("instance") );
		if( handle == HAZEL_INVALID_HANDLE_VALUE )
			ThrowException1( NullException, BT_TEXT("handle") );

		instance_ = instance;
		m_handle_ = handle;
	}

	void fini()
	{
		instance_ = 0;
		m_handle_ = HAZEL_INVALID_HANDLE_VALUE;
	}

	virtual int open( void* connection )
	{
		return instance_->register_handle( m_handle_, connection );
	}

	Hazel_HANDLE getHandle() const
	{
		return m_handle_;
	}

	void setHandler( Hazel_Operation_Result& handler )
	{
		handler_ = &handler;
	}


	//void complete (size_t bytes_transferred,
 //                        int success,
 //                        const void *completion_key,
 //                        u_long error )
	//{
	//	ASSERT( NULL != handler_);
	//	handler_->complete( bytes_transferred
	//						, success
	//						, completion_key
	//						, error );
	//}

protected:
	Hazel_HANDLE m_handle_;
	WIN32_Operation_Proactor* instance_;
	//Hazel_Operation_Result* handler_;
};

_networks_begin

#endif //HAZEL_WIN32_OPERATION_OVERLAPPED_H