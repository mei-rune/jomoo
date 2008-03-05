
#include "TCP_Asynch_Read_Result.h"
#include "TcpTransport.h"
#include "Base/lastError.h"
#include "Instance_TCP.H"
#include "../Template/Transport.H"

#ifdef _MEMORY_DEBUG
#undef THIS_FILE
#define new	   DEBUG_NEW  
#define malloc DEBUG_MALLOC  
static char THIS_FILE[] = __FILE__;  
#endif // _MEMORY_DEBUG

_networks_begin

TCP_Read_Result::TCP_Read_Result( )
: m_channel_( 0 )
, m_handle_( 0 )
, m_buffer_( 0 )
, m_length_( 0 )
{
}

void TCP_Read_Result::init( Instance_TCP* instance
		, TcpTransport* channel
		, handler_type* handle
		, void* buffer
		, size_t length
		, void * act )
{
	ASSERT( channel != 0 );
		TCP_Asynch_Result::init( instance,
		reinterpret_cast< JOMOO_HANDLE > ( channel->get_handle().get_handle()) , act );


	ASSERT( handle != 0 );
	ASSERT( buffer != 0 );
	ASSERT( length > 0 );
	m_channel_ = channel;
	m_handle_ = handle;
	m_buffer_ = buffer;
	m_length_ = length;
}

void TCP_Read_Result::fini( )
{
	TCP_Asynch_Result::fini();
}

void* TCP_Read_Result::buffer()
{
	return m_buffer_;
}

const void* TCP_Read_Result::buffer() const
{
	return m_buffer_;
}

size_t TCP_Read_Result::length() const
{
	return m_length_;
}

TCP_Read_Result::handler_type& TCP_Read_Result::handle()
{
	return *m_handle_;
}


TcpTransport& TCP_Read_Result::native_transport()
{
	return *m_channel_;
}

JOMOO_Transport& TCP_Read_Result::transport()
{
	return *m_channel_;
}

void TCP_Read_Result::complete (size_t bytes_transferred,
									   int success,
									   const void *completion_key,
									   u_long error)
{
	m_bytes_transferred_ = bytes_transferred;
	m_error_ = error;
	m_success_= success;
//	m_handle_.onRead( *this );
	Read_Result_T< TCP_Read_Result , JOMOO_Read_Result > r( *this, handle(), transport() );
	m_handle_->onRead ( r );
}


_networks_end
