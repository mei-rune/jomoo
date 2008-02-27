

#include "TcpAcceptor.h"
#include "Hazel.Base/lastError.h"
#include "Instance_TCP.H"
#include "Hazel.Base/Memory/Memory.H"
#include "../Template/Acceptor.H"

#ifdef _MEMORY_DEBUG
#undef THIS_FILE
#define new	   DEBUG_NEW  
#define malloc DEBUG_MALLOC  
static char THIS_FILE[] = __FILE__;  
#endif // _MEMORY_DEBUG

_networks_begin

const static int addrbufsize = sizeof (sockaddr_in)*2 + sizeof (sockaddr)*2 + 100;

TCP_Accept_Result::TCP_Accept_Result( )
: m_acceptor_( 0 )
, m_handle_( 0 )
, m_new_channel_(  )
, m_buf_( 0 )
, m_bytes_transferred_( 0 )
{
}

TCP_Accept_Result::~TCP_Accept_Result()
{
	if( m_buf_ != 0 )
		_memory boe_free( m_buf_ );
}

void TCP_Accept_Result::init( Instance_TCP* instance
		, TcpAcceptor* channel
		, handler_type* handle
		, TcpTransportPtr newchannel
		, int recv_size
		, void * act )
{
	ASSERT( channel != 0 );
	ASSERT( newchannel.get() != 0 );
	TCP_Asynch_Result::init( instance,
		reinterpret_cast< Hazel_HANDLE > ( channel->get_handle().get_handle()) , act );

	ASSERT( handle != 0 );
	m_acceptor_ = channel;
	m_handle_ = handle;
	m_new_channel_ = newchannel;

	m_buf_len_ = addrbufsize + recv_size;
	
	if( m_buf_ != 0 )
	{
		_memory boe_free( m_buf_ );
		m_buf_ = 0;
	}
	m_buf_ = ( char* )_memory boe_malloc( m_buf_len_ , __FILE__,__LINE__ );
	//memset( m_buf_ , 0 , m_buf_len_ );
	//m_buf_[ m_buf_len_ - 2 ] = 3;

}

void TCP_Accept_Result::fini( )
{
	TCP_Asynch_Result::fini();
	if( m_buf_ != 0 )
	{
		_memory boe_free( m_buf_ );
		m_buf_ = 0;
	}
}

TcpAcceptor& TCP_Accept_Result::native_acceptor()
{
	return *m_acceptor_;
}

TcpTransportPtr TCP_Accept_Result::new_native_channel()
{
	return m_new_channel_;
}

TCP_Accept_Result::handler_type& TCP_Accept_Result::handle()
{
	return *m_handle_;
}

Hazel_Transport_Ptr TCP_Accept_Result::new_channel()
{
	return m_new_channel_;
}

Hazel_Acceptor& TCP_Accept_Result::acceptor()
{
	return *m_acceptor_;
}

//TcpTransport* TCP_Accept_Result::new_TcpTransport()
//{
//	return new_transport_;
//}

char* TCP_Accept_Result::getBuffer( )
{
	return m_buf_+addrbufsize;
}

size_t TCP_Accept_Result::getBufferLen() const
{
	return m_buf_len_ - addrbufsize;
}

void TCP_Accept_Result::complete (size_t bytes_transferred,
										 int success,
										 const void *completion_key,
										 u_long error)
{
	m_error_ = error;
	m_bytes_transferred_ = bytes_transferred;
	m_success_= success;

	sockaddr *local_addr = 0;
	sockaddr *remote_addr = 0;
	int local_size = 0;
	int remote_size = 0;

	::GetAcceptExSockaddrs ( getBuffer (),
		static_cast < DWORD >( bytes_transferred),
		static_cast < DWORD >( sizeof (sockaddr_in) + sizeof (sockaddr) ),
		static_cast < DWORD >( sizeof (sockaddr_in) + sizeof (sockaddr) ),
		&local_addr,
		&local_size,
		&remote_addr,
		&remote_size);

	m_new_channel_->getRemoteAddr().set_addr ( remote_addr,remote_size);
	m_new_channel_->getLocalAddr().set_addr ( local_addr,local_size);

	m_new_channel_->onAccept( );

	BT_LOG_TRACE( m_new_channel_->getLogger(), m_new_channel_->toString() << BT_TEXT("TCP连接到来!") );

	//if( instance_.getWIN32Proactor().register_handle( ( Hazel_HANDLE )( m_new_channel_->get_handle().get_handle() ), 0 ) != 0 )
	//{
	//	m_success_ = -1;
	//	BT_LOG_ERROR( m_new_channel_->getLogger(), m_new_channel_->toString() << BT_TEXT("打开异步连接失败，[")
	//	<< lastError() << BT_TEXT("]") );
	//}

	Hazel_HANDLE listener = ( Hazel_HANDLE )m_acceptor_->get_handle().get_handle();
	setsockopt( m_acceptor_->get_handle().get_handle(), SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT,
			(char *) &listener, sizeof listener );

//	m_handle_.onAccept( *this );
	//Acceptor_T< TcpAcceptor,  handler_type::result_type::acceptor_type > a(* acceptor() );
	Accept_Result_T< TCP_Accept_Result, handler_type::result_type > r( *this , handle(),acceptor() );
	m_handle_->onAccept( r );
}



TcpAcceptor::TcpAcceptor( Instance_TCP& instance , const tchar* name )
: instance_( instance )
, accept_Overlapped_ ( )
, toString_( name == 0 ? BT_TEXT( "接收器" ):name )
{
}

TcpAcceptor::~TcpAcceptor(void)
{
}

bool TcpAcceptor::isOpen( )
{
	if( m_handle_.get_handle() != NULL && m_handle_.get_handle() != INVALID_SOCKET )
		return true;
	return false;
}


bool TcpAcceptor::open( const Hazel_INET_Addr& addr )
{
	if( m_handle_.get_handle() != NULL && m_handle_.get_handle() != INVALID_SOCKET )
		BT_LOG_ERROR_RETURN( getLogger(), toString() << BT_TEXT("已经打开过了!") , false );

	m_serveraddr_ = addr;

	if( m_handle_.open( ) != 0 )
		BT_LOG_ERROR_RETURN( getLogger(), BT_TEXT("打开socket失败，[")
		<< lastError() << BT_TEXT("]") , false );

	if( ::bind( m_handle_.get_handle()
		, ( sockaddr* )m_serveraddr_.get_addr()
		, m_serveraddr_.get_size() ) == SOCKET_ERROR )
		BT_LOG_ERROR_RETURN( getLogger(), BT_TEXT("绑定服务到地址[")<< 
		m_serveraddr_.toString() << BT_TEXT("]失败，[")
		<< lastError() << BT_TEXT("]") , false );

	if( ::listen( m_handle_.get_handle(), SOMAXCONN ) == SOCKET_ERROR )
		BT_LOG_ERROR_RETURN( getLogger(), BT_TEXT("监听服务启动失败，[")
		<< lastError() << BT_TEXT("]") , false );

	if( instance_.getInstanceNetwork().getNativeProactor().register_handle( 
		reinterpret_cast< Hazel_HANDLE > ( m_handle_.get_handle() )
		, this ) != 0 )
		BT_LOG_ERROR_RETURN( getLogger(), BT_TEXT("打开异步监听失败，[")
		<< lastError() << BT_TEXT("]") , false );

	BT_LOG_INFO( getLogger(), BT_TEXT("监听服务启动成功，监听地址[")<< 
		m_serveraddr_.toString() << BT_TEXT("]") );

	toString_ = BT_TEXT( "接收器[" );
	toString_ += addr.toString();
	toString_ += BT_TEXT( "]");

	return true;
}

void TcpAcceptor::close( )
{
	m_handle_.close();
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

TcpTransportPtr TcpAcceptor::createTransport()
{
	return TcpTransportPtr( instance_.getTransportFactory().create( &instance_ , "Tcp" )
		,transport_deleter( &instance_ ) ) ;
}

bool TcpAcceptor::accept( handler_type& handle
							/*,Hazel_Transport& new_tcp_channel*/
							, void* act )
{
	TcpTransportPtr newchannel = createTransport();

   if( !newchannel->open() )
		BT_LOG_ERROR_RETURN( getLogger(), toString() << BT_TEXT("打开TCP连接失败，[") 
		<< lastError( WSAGetLastError() ) << BT_TEXT("]") , false );
	
	Instance_TCP::AcceptResultFactory::auto_ptr result (
		instance_.getAcceptResultFactory().create( &instance_, this , &handle , newchannel, 0,act ) 
		, instance_.getAcceptResultFactory() );

//#ifdef _WINXP_
	 DWORD address_size = sizeof (sockaddr_in) + sizeof (sockaddr);
	DWORD bytes_transferred = 0;
	if( ::AcceptEx( m_handle_.get_handle()
		, result->new_native_channel()->get_handle().get_handle()
		, result->getBuffer()
		, ( DWORD )bytes_transferred
		, address_size
		, address_size
		, &bytes_transferred
		, result.get() ) != TRUE )
	{
		if ( GetLastError() != ERROR_IO_PENDING )
			BT_LOG_ERROR_RETURN( getLogger(), toString() << BT_TEXT("监听TCP连接失败，[")
			<< lastError( WSAGetLastError() ) << BT_TEXT("]") , false );
	}
	result.release();
	return true;
//#else
//	char remote_addr[1024];
//	int remote_size = 1024;
//
//
//	hazel_sap_HANDLE new_socket = ::accept( get_handle().get_handle( )
//		, ( sockaddr* )remote_addr
//		, &remote_size );
//
//   if( new_socket == INVALID_SOCKET ) 
//		BT_LOG_ERROR_RETURN( getLogger(), toString() << BT_TEXT("建立TCP连接失败，[") << lastError() << BT_TEXT("]") , false );
//
//    result->new_tcp_channel()->get_handle().set_handle( new_socket );
//   result->new_tcp_channel()->getRemoteAddr().set_addr ( &remote_addr,remote_size);
//
//	//if( instance_.getInstance_IO().getProactor()->register_handle( ( Hazel_HANDLE )result->new_tcp_channel()->get_handle().get_handle(), 0 ) != 0 )
//	//		BT_LOG_ERROR_RETURN( getLogger(), toString() << BT_TEXT("打开异步连接失败，[")
//	//	<< lastError() << BT_TEXT("]") , false );
//
//	result->complete( 0, 0, 0, 0 );
//
//#endif //
}

bool TcpAcceptor::cancel()
{
	return ( CancelIo( ( Hazel_HANDLE )m_handle_.get_handle() ) ) ? true : false ;
}

hazel_socket& TcpAcceptor::get_handle()
{
	return m_handle_;
}

TcpAcceptor::LoggerPtr TcpAcceptor::getLogger()
{
	return instance_.getInstanceNetwork().getLogger();
}

const tstring& TcpAcceptor::toString() const
{
	return toString_;
}

_networks_end
