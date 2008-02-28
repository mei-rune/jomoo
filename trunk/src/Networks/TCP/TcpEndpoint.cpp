
#include "Instance_TCP.H"
#include "TcpEndpoint.h"
#include "Instance_TCP.H"
#include "Hazel.Base/lastError.H"
#include "Hazel.Base/Exception.HPP"
#ifdef _MEMORY_DEBUG
#undef THIS_FILE
#define new	   DEBUG_NEW  
#define malloc DEBUG_MALLOC  
static char THIS_FILE[] = __FILE__;  
#endif // _MEMORY_DEBUG

_networks_begin

tstring TcpEndpoint::protocol_( "tcp" );

//TcpEndpoint::TcpEndpoint( Instance_TCP& instance, const tstring& ipstr, const tstring& port )
//: instance_( instance )
//, addr_( port.c_str(), ipstr.c_str() )
//{
//	toString_ = BT_TEXT( "TCP¶Ëµã[" );
//	toString_ += addr_.toString();
//	toString_ += BT_TEXT( "]" );
//}

//TcpEndpoint::TcpEndpoint( Instance_TCP& instance, const tstring& url )
//: instance_( instance )
//, addr_( url.c_str() )
//{
//	toString_ = BT_TEXT( "TCP¶Ëµã[" );
//	toString_ += addr_.toString();
//	toString_ += BT_TEXT( "]" );
//}

TcpEndpoint::TcpEndpoint(void)
: instance_( 0 )
, addr_( )/*
, connector_( )
, acceptor_()*/
, toString_( BT_TEXT( "TCP¶Ëµã" ) )
{
}

TcpEndpoint::~TcpEndpoint(void)
{
}


void TcpEndpoint::init( Instance_TCP* instance, const Hazel_Url_Base* url )
{
	if( instance == 0 )
		ThrowException1( NullException, BT_TEXT("instance") );

	if( url == 0 )
		ThrowException1( NullException, BT_TEXT("url") );

	instance_ = instance;
	addr_.set( url->address().c_str() );
}

void TcpEndpoint::fini( )
{
}

const std::string& TcpEndpoint::protocol() const
{
	return protocol_;
}

const std::string& TcpEndpoint::toString() const
{
	return toString_;
}

int TcpEndpoint::type() const
{
	return nTcpTransport;
}

Hazel_Connector& TcpEndpoint::connector() const
{
	if( connector_.get() != 0 )
		return *connector_;
	std::auto_ptr< TcpConnector > connector( new TcpConnector( *instance_ ) );
	if( !connector->open( addr_ ) )
		ThrowException1( SystemException, lastError() );
	connector_ = connector;
	return *connector_;
}

Hazel_Acceptor& TcpEndpoint::acceptor( ) const
{
	if( acceptor_.get() != 0 )
		return *acceptor_;
	std::auto_ptr< TcpAcceptor > acceptor( new TcpAcceptor( *instance_ ) );
	if( !acceptor->open( addr_ ) )
		ThrowException1( SystemException, lastError() );
	acceptor_ = acceptor;
	return *acceptor_;
}

void TcpEndpoint::release()
{
	instance_->getEndpiontFactory().release( this );
}

_networks_end
