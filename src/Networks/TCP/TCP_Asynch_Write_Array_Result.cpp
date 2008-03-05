

#include "TCP_Asynch_Write_Array_Result.h"
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

TCP_Write_Array_Result::TCP_Write_Array_Result()
: m_channel_( 0 )
, m_handle_( 0 )
, m_data_( 0 )
, m_size_( -1 )
{
}


void TCP_Write_Array_Result::init( Instance_TCP* instance
							, TcpTransport* channel
							, handler_type* handle
							, const iovec* data
							, size_t length
							, void * act )
{
	ASSERT( channel != 0 );
	TCP_Asynch_Result::init( instance,
		reinterpret_cast  < JOMOO_HANDLE > ( channel->get_handle().get_handle()) , act );

	ASSERT( handle != 0 );
	ASSERT( data != 0 );
	ASSERT( length > 0 );
	m_channel_ = channel;
	m_handle_ = handle;
	m_data_ = data;
	m_size_ = length;
}

void TCP_Write_Array_Result::fini( )
{
	TCP_Asynch_Result::fini();
}

const iovec* TCP_Write_Array_Result::data()
{
	return m_data_;
}

size_t TCP_Write_Array_Result::size() const
{
	return m_size_;
}

TCP_Write_Array_Result::handler_type& TCP_Write_Array_Result::handle()
{
	return *m_handle_;
}

TcpTransport& TCP_Write_Array_Result::native_transport()
{
	return *m_channel_;
}

JOMOO_Transport& TCP_Write_Array_Result::transport()
{
	return *m_channel_;
}

void TCP_Write_Array_Result::complete (size_t bytes_transferred,
										   int success,
										   const void *completion_key,
										   u_long error )
{
	m_bytes_transferred_ = bytes_transferred;
	m_error_ = error;
	m_success_= success;
//	m_handle_.onWriteArray( *this );

	Write_Array_Result_T< TCP_Write_Array_Result , JOMOO_Write_Array_Result > r( *this, handle(), transport() );
	m_handle_->onWriteArray( r );

}
_networks_end
