#include "TcpAsynchResult.h"
#include "TcpTransport.H"
#include "Hazel.Base/lastError.H"
#include "Hazel.Base/toString.H"
#include "Instance_TCP.H"

#ifdef _MEMORY_DEBUG
#undef THIS_FILE
#define new	   DEBUG_NEW  
#define malloc DEBUG_MALLOC  
static char THIS_FILE[] = __FILE__;  
#endif // _MEMORY_DEBUG

_networks_begin

TcpTransport::TcpTransport( )
: instance_( 0 )
{
}

TcpTransport::~TcpTransport(void)
{
	close();
}

void TcpTransport::init( Instance_TCP* instance , const tchar* name )
{
	if( NULL == instance )
		ThrowException1( NullException, BT_TEXT("instance") );
	instance_ = instance;
	m_to_string_ = name == 0 ? BT_TEXT(""):name;
}

void TcpTransport::fini()
{
}

bool TcpTransport::open( )
{
	if( m_handle_.get_handle() != NULL && m_handle_.get_handle() != INVALID_SOCKET )
		LOG_ERROR_RETURN( getLogger(), BT_TEXT("已经打开过了!") , false );

	if( m_handle_.open( ) != 0 )
		LOG_ERROR_RETURN( getLogger(), BT_TEXT("打开socket失败，[")
		<< lastError() << BT_TEXT("]") , false );

	return true;
}

void TcpTransport::close( )
{
	if( m_handle_.get_handle() != NULL && m_handle_.get_handle() != INVALID_SOCKET )
		LOG_ERROR( getLogger(),toString() << BT_TEXT("TCP连接断开!") );
	
	m_handle_.close();
}

bool TcpTransport::write(handler_type& handle,
						   const void* buffer,
						   size_t length,
						   void* act )
{
	Instance_TCP::WriteResultFactory::auto_ptr result (
		instance_->getWriteResultFactory().create( instance_,this, &handle, buffer, length ,act )
		, instance_->getWriteResultFactory() );

	if( !m_handle_.send( buffer, length, result->getOverlapped() ) )
	{
		if ( GetLastError() != ERROR_IO_PENDING )
			LOG_ERROR_RETURN( getLogger(), toString() << BT_TEXT("发送数据失败，[") 
			<< lastError() << BT_TEXT("]") , false );
	}
	result.release();
	return true;
}

bool TcpTransport::write(handler_type& handle,
							  const iovec* data,
							  size_t size,
							  void* act )
{
	Instance_TCP::WriteArrayResultFactory::auto_ptr result ( 
		instance_->getWriteArrayResultFactory().create( instance_, this, &handle, data, size ,act )
		, instance_->getWriteArrayResultFactory() );

	if( ! m_handle_.sendv( data, size, result->getOverlapped() ) )
	{
		if ( GetLastError() != ERROR_IO_PENDING )
			LOG_ERROR_RETURN( getLogger(), toString() << BT_TEXT("传输数据失败，[") << 
			lastError() << BT_TEXT("]") , false );
	}
	result.release();
	return true;
}

bool TcpTransport::transmit(handler_type& handle,
							  const iopack* data,
							  size_t size,
							  void* act )
{
	Instance_TCP::TransmitResultFactory::auto_ptr result ( 
		instance_->getTransmitResultFactory().create( instance_, this, &handle, data, size ,act )
		, instance_->getTransmitResultFactory() );

	if( ! m_handle_.transmit( data, size, result->getOverlapped() ) )
	{
		if ( GetLastError() != ERROR_IO_PENDING )
			LOG_ERROR_RETURN( getLogger(), toString() << BT_TEXT("传输数据失败，[") << 
			lastError() << BT_TEXT("]") , false );
	}
	result.release();
	return true;
}


bool TcpTransport::read(handler_type& handle,
						  void* buffer,
						  size_t length,
						  void* act )
{
	Instance_TCP::ReadResultFactory::auto_ptr result (
		instance_->getReadResultFactory().create( instance_, this, &handle, buffer,length ,act )
		, instance_->getReadResultFactory() );

	if( ! m_handle_.recv( buffer,length , result->getOverlapped() ) )
	{
		if ( GetLastError() != ERROR_IO_PENDING )
			LOG_ERROR_RETURN( getLogger(), toString() << BT_TEXT("读取数据失败，[") 
			<< lastError() << BT_TEXT("]") , false );
	}
	result.release();
	return true;
}


bool TcpTransport::read(handler_type& handle,
						  iovec* data,
						  size_t size,
						  void* act )
{
	Instance_TCP::ReadArrayResultFactory::auto_ptr result (
		instance_->getReadArrayResultFactory().create( instance_, this, &handle, data,size ,act )
		, instance_->getReadArrayResultFactory() );

	if( ! m_handle_.recvv( data,size , result->getOverlapped() )  )
	{
		if ( GetLastError() != ERROR_IO_PENDING )
			LOG_ERROR_RETURN( getLogger(), toString() << BT_TEXT("读取数据失败，[") 
			<< lastError() << BT_TEXT("]") , false );
	}
	result.release();
	return true;
}

int TcpTransport::setFeature(const char* feature,
								bool value)
{
	return -1;
}

int TcpTransport::getFeature(const char* feature,
								bool& value) const
{
	return -1;
}

int TcpTransport::setOption(const char* option,
							   void* value,
							   size_t size)
{
	return -1;
}


int TcpTransport::getOption(const char* option,
							   void* value,
							   size_t& size) const
{
	if( _tcsicmp( option, "localaddr" ) == 0 )
	{
		if( m_localaddr_.get_size() < size )
			return -1;
		memcpy( value, m_localaddr_.get_addr() , m_localaddr_.get_size() );
		return 0;
	}
	else if( _tcsicmp( option, "remoteaddr" ) == 0 )
	{
		if( m_remoteaddr_.get_size() < size )
			return -1;
		memcpy( value, m_remoteaddr_.get_addr() , m_remoteaddr_.get_size() );
		return 0;
	}
	return -1;
}

bool TcpTransport::cancel()
{
	return ( CancelIo( ( Hazel_HANDLE )m_handle_.get_handle() ) ) ? true : false ;
}

const Hazel_INET_Addr& TcpTransport::getRemoteAddr() const
{
	return m_remoteaddr_;
}
//const Hazel_INET_Addr& TcpTransport::getRemoteAddr() const
//{
//	return m_remoteaddr_;
//}

Hazel_INET_Addr& TcpTransport::getRemoteAddr()
{
	return m_remoteaddr_;
}

const Hazel_INET_Addr& TcpTransport::getLocalAddr() const
{
	return m_localaddr_;
}

Hazel_INET_Addr& TcpTransport::getLocalAddr()
{
	return m_localaddr_;
}

TcpTransport::LoggerPtr TcpTransport::getLogger()
{
	return instance_->getInstanceNetwork().getLogger();
}

const tstring& TcpTransport::toString() const
{
	return m_to_string_;
}

hazel_socket& TcpTransport::get_handle()
{
	return m_handle_;
}

void TcpTransport::onConnect()
{
	m_to_string_ = BT_TEXT( "TCP通信器[" );
	m_to_string_ += m_remoteaddr_.toString();
	m_to_string_ += BT_TEXT( "]" );
}

void TcpTransport::onAccept()
{
	m_to_string_ = BT_TEXT( "TCP通信器[" );
	m_to_string_ += m_remoteaddr_.toString();
	m_to_string_ += BT_TEXT( "]" );

	if( instance_->getInstanceNetwork().getNativeProactor().register_handle(
		reinterpret_cast  < Hazel_HANDLE >( get_handle().get_handle() ) , this ) != 0 )
			LOG_ERROR_THROW( getLogger(), toString() << BT_TEXT("打开异步连接失败，[") 
			<< lastError() << BT_TEXT("]") , SystemException );
}

//	//int TimeOut = instance_->getConfig()->getPropertyAsIntWithDefault( "Hazel.Networks.TimeOut" , 5000 );
//
//	//m_handle_.set_option( SOL_SOCKET, SO_RCVTIMEO, &TimeOut, sizeof( long ) );
//	//m_handle_.set_option( SOL_SOCKET, SO_SNDTIMEO, &TimeOut, sizeof( long ) );
//}

_networks_end
