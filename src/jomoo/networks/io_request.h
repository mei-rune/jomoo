
#ifndef JOMOO_WIN32_OPERATION_OVERLAPPED_H
#define JOMOO_WIN32_OPERATION_OVERLAPPED_H

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include "config_Networks.h"
#include "jomoo/counter_ptr.hpp"

_networks_begin

class io_request
	: public JOMOO_OVERLAPPED
{
public:

	io_request( )
		: instance_( 0 )
		, m_handle_( JOMOO_INVALID_HANDLE_VALUE )
	{
		Internal =  0;
		InternalHigh =  0;
		Offset =  0;
		OffsetHigh =  0;
		hEvent = 0;
	}

	virtual ~io_request(void)
	{
	}

	void init( proactor& instance , JOMOO_HANDLE handle )
	{
		if( handle == JOMOO_INVALID_HANDLE_VALUE )
			ThrowException1( NullException, BT_TEXT("handle") );

		instance_ = &instance;
		m_handle_ = handle;
	}

	void fini()
	{
		instance_ = 0;
		m_handle_ = JOMOO_INVALID_HANDLE_VALUE;
	}

	virtual bool bind( void* connection )
	{
		return instance_->register_handle( m_handle_, connection );
	}

	JOMOO_HANDLE get_handle() const
	{
		return m_handle_;
	}

    void incRef()
	{
		counter_.increment();
	}
    
	void decRef()
	{
		if( 0 >= counter_.decrement() )
			release( );
	}

	virtual bool post() = 0;
	virtual void on_complete (size_t bytes_transferred,
                         int success,
                         const void *completion_key,
                         u_long error = 0) = 0;

protected:

	virtual void release()
	{
		delete this;
	}

	JOMOO_HANDLE m_handle_;
	proactor* instance_;
private:
	counter counter_;
};

_networks_begin

#endif //JOMOO_WIN32_OPERATION_OVERLAPPED_H