
#ifndef ___iopack___
#include "TCPAsynchResult.h"
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

TCP_Transmit_Result::TCP_Transmit_Result(  )
: m_channel_( 0 )
, m_handle_( 0 )
, m_data_( 0 )
, m_size_( -1 )
{
}
void TCP_Transmit_Result::init( Instance_TCP* instance
							, TcpTransport* channel
							, handler_type* handle
							, const iopack* data
							, size_t size
							, void * act )
{
	ASSERT( channel != 0 );
		TCP_Asynch_Result::init( instance,
		reinterpret_cast< JOMOO_HANDLE > ( channel->get_handle().get_handle()) , act );

	ASSERT( handle != 0 );
	ASSERT( data != 0 );
	ASSERT( size > 0 );
	m_channel_ = channel;
	m_handle_ = handle;
	m_data_ = data;
	m_size_ = size;
}

void TCP_Transmit_Result::fini( )
{
	TCP_Asynch_Result::fini();
}

const iopack* TCP_Transmit_Result::data() const
{
	return m_data_;
}

size_t TCP_Transmit_Result::size() const
{
	return m_size_;
}

TCP_Transmit_Result::handler_type& TCP_Transmit_Result::handle()
{
	return *m_handle_;
}

TcpTransport& TCP_Transmit_Result::native_transport()
{
	return *m_channel_;
}

JOMOO_Transport& TCP_Transmit_Result::transport()
{
	return *m_channel_;
}

void TCP_Transmit_Result::complete (size_t bytes_transferred,
										   int success,
										   const void *completion_key,
										   u_long error )
{
	m_bytes_transferred_ = bytes_transferred;
	m_error_ = error;
	m_success_= success;
	//m_handle_.onTransmit( *this );
	Transmit_Result_T< TCP_Transmit_Result , JOMOO_Transmit_Result > r( *this, handle(), transport() );
	m_handle_->onTransmit ( r );

}

_networks_end

#endif