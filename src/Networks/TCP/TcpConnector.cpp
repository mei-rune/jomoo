
#include "TcpConnector.h"
#include "Base/lastError.h"
#include "TcpTransport.h"
#include "Instance_TCP.H"
#include "../Template/Connector.H"

#ifdef _MEMORY_DEBUG
#undef THIS_FILE
#define new	   DEBUG_NEW  
#define malloc DEBUG_MALLOC  
static char THIS_FILE[] = __FILE__;  
#endif // _MEMORY_DEBUG

_networks_begin

TCP_Connect_Result::TCP_Connect_Result( )
: m_channel_( 0 )
, m_handle_( 0 )
, m_Transport_( )
{
}

TCP_Connect_Result::~TCP_Connect_Result()
{
}

void TCP_Connect_Result::init( Instance_TCP* instance
		, TcpConnector* channel
		, handler_type* handle
		, TcpTransportPtr newchannel
		, void * act )
{
	ASSERT( channel != 0 );
	ASSERT( newchannel.get() != 0 );
	TCP_Asynch_Result::init( instance,
		reinterpret_cast< JOMOO_HANDLE > ( newchannel->get_handle().get_handle()) , act );

	ASSERT( handle != 0 );
	m_channel_ = channel;
	m_handle_ = handle;
	m_Transport_ = newchannel;
}

void TCP_Connect_Result::fini( )
{
	TCP_Asynch_Result::fini();
}

//TcpTransport* TCP_Connect_Result::new_channel()
//{
//	return m_TcpTransport_;
//}

TCP_Connect_Handler& TCP_Connect_Result::handle()
{
	return *m_handle_;
}

TcpConnector& TCP_Connect_Result::native_connector()
{
	return *m_channel_;
}
	
TcpTransportPtr TCP_Connect_Result::new_native_channel()
{
	return m_Transport_;
}

JOMOO_Transport_Ptr TCP_Connect_Result::new_channel()
{
	return dynamicCast< JOMOO_Transport , TcpTransport >( m_Transport_ );
}

JOMOO_Connector& TCP_Connect_Result::connector()
{
	return *m_channel_;
}

void TCP_Connect_Result::complete (size_t bytes_transferred,
										  int success,
										  const void *completion_key,
										  u_long error )
{
	m_error_ = error;
	m_success_= success;

	new_native_channel()->getRemoteAddr() = m_channel_->getRemoteAddr();
	new_native_channel()->get_handle().get_local_addr( new_native_channel()->getLocalAddr() );

	m_Transport_->onConnect();

	LOG_TRACE( m_Transport_->getLogger(), m_Transport_->toString() << BT_TEXT("TCP连接建立成功!") );

	//m_handle_.onConnect( *this );
	//Connector_T< TcpConnector,  handler_type::result_type::connector_type > a( connector() );
	Connect_Result_T< TCP_Connect_Result, handler_type::result_type > r( *this , handle(),native_connector() );
	m_handle_->onConnect( r );
}


TcpConnector::TcpConnector( Instance_TCP& instance , const tchar* name )
: instance_( instance )
, toString_( name == 0 ? BT_TEXT( "连接器" ):name )
{
}

TcpConnector::~TcpConnector(void)
{
}

struct transport_deleter
{
	Instance_TCP* instance_;

	transport_deleter( Instance_TCP* instance )
		: instance_( instance )
	{
	}

    void operator()(TcpTransport * p)
    {
        if(p) instance_->getTransportFactory().release(p);
    }
};

TcpTransportPtr TcpConnector::createTransport()
{
	return TcpTransportPtr( instance_.getTransportFactory().create( &instance_ , "Tcp" )
		,transport_deleter( &instance_ ) ) ;
}

bool TcpConnector::connect(TCP_Connect_Handler& handle, void* act )
{
	TcpTransportPtr newchannel = createTransport();

   if( !newchannel->open() )
		LOG_ERROR_RETURN( getLogger(), toString() << BT_TEXT("打开TCP连接失败，[") 
		<< lastError( WSAGetLastError() ) << BT_TEXT("]") , false );
	
   Instance_TCP::ConnectResultFactory::auto_ptr result (
		instance_.getConnectResultFactory().create ( &instance_ , this, &handle,newchannel, act )
		, instance_.getConnectResultFactory() );

#ifdef _WINXP_

   	if( result->getOverlapped().open( this ) )
			LOG_ERROR_RETURN( getLogger(), toString() << BT_TEXT("打开异步连接失败，[")
		<< lastError() << BT_TEXT("]") , false );

	if( ::ConnectEx( result->new_native_channel()->get_handle().get_handle()
		, (const struct sockaddr*)m_remoteaddr_.get_addr()
		, (int)m_remoteaddr_.get_size()
		, 0
		, 0
		, 0
		, result->getOverlapped() ) != TRUE )
	{
		if ( GetLastError() != ERROR_IO_PENDING )
			LOG_ERROR_RETURN( getLogger(), toString() << BT_TEXT("建立TCP连接失败，[") << lastError() << BT_TEXT("]") , false );
	}
	return true;
#else
	if( ::connect( result->new_native_channel()->get_handle().get_handle(),
		( const sockaddr *)m_remoteaddr_.get_addr(),m_remoteaddr_.get_size() ) == SOCKET_ERROR ) 
		LOG_ERROR_RETURN( getLogger(), toString() << BT_TEXT("建立TCP连接失败，[")
				<< lastError() << BT_TEXT("]") , false );

	if( result->getOverlapped().open( this ) )
			LOG_ERROR_RETURN( getLogger(), toString() << BT_TEXT("打开异步连接失败，[")
		<< lastError() << BT_TEXT("]") , false );

	result->complete( 0, 0, 0, 0 );
	result.release();
	return true;
#endif // _WINXP_
}

bool TcpConnector::cancel()
{
	#ifdef _WINXP_
	return 	false ;

	#else
	return false;
	#endif // _WINXP_
}

bool TcpConnector::isOpen( )
{
	return true;
}

bool TcpConnector::open( const JOMOO_INET_Addr& addr )
{
	m_remoteaddr_.set_addr( addr.get_addr(), addr.get_size() );
	toString_ = BT_TEXT( "连接器[" );
	toString_ += addr.toString();
	toString_ += BT_TEXT( "]");
	return true;
}
void TcpConnector::close( )
{
}

TcpConnector::LoggerPtr TcpConnector::getLogger()
{
	return instance_.getInstanceNetwork().getLogger();
}


const JOMOO_INET_Addr& TcpConnector::getRemoteAddr() const
{
	return m_remoteaddr_;
}

const tstring& TcpConnector::toString() const
{
	return toString_;
}

_networks_end
