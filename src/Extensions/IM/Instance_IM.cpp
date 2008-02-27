#include "StdAfx.h"
#include "Instance_IM.h"
#include "BOE/exception.hpp"
#include "Message_Transport_Endpoint.H"
#include <queue>

#ifdef _MEMORY_DEBUG
#undef THIS_FILE
#define new	   DEBUG_NEW  
#define malloc DEBUG_MALLOC  
static char THIS_FILE[] = __FILE__;  
#endif // _MEMORY_DEBUG

_im_begin

Instance_IM::Instance_IM( _io Instance_IO& ioinstance )
: ioinstance_( ioinstance )
, messaging_factory_( 0 )
, concurrency_( 0 )
, toString_( BT_TEXT("Instance_IM") )
{
}

Instance_IM::~Instance_IM(void)
{
	close();
}

int Instance_IM::open( _util PropertiesPtr config )
{
	overrides_.maxMessageSize = config->getPropertyAsIntWithDefault( "BOE.IM.maxMessageSize", 1024 * 6 );
	return 0;
}

void Instance_IM::close( )
{
	//ioinstance_.close( );
}

bool Instance_IM::isStop()
{
	return ioinstance_.isStop();
}

Instance_IM::LoggerPtr Instance_IM::getLogger()
{
	return ioinstance_.getLogger();
}

void Instance_IM::setLogger( LoggerPtr ptr )
{
	ioinstance_.setLogger( ptr );
}

Instance_IO& Instance_IM::getIOInstance()
{
	return ioinstance_;
}

const Instance_IM::DefaultsAndOverrides& Instance_IM::getDefaultsAndOverrides()const
{
	return overrides_;
}

void Instance_IM::setConcurrencyBridge( _kernel BOE_Concurrency_Impl& concurrency )
{
	concurrency_ = &concurrency;
}

BOE_Concurrency_Impl& Instance_IM::getConcurrencyBridge()
{
	if( concurrency_ == 0 )
		BT_LOG_ERROR_THROW( getLogger(),
		toString() << BT_TEXT("> ConcurrencyBridge不能为空"), RuntimeException );
	return *concurrency_;
}

Instance_IM::endpoint_ptr Instance_IM::createEndpoint(  const tstring& addr )
{
	return endpoint_ptr( new endpoint_type( *this, addr ) );
}

Instance_IM::acceptor_ptr Instance_IM::createAcceptor( const tstring& addr )
{
	return acceptor_ptr( new acceptor_type( *this, addr ) );
}

Instance_IM::connector_ptr Instance_IM::createConnector( const tstring& addr )
{
	return connector_ptr( new connector_type( *this, addr ) );
}

Instance_IM::connection_ptr Instance_IM::createConnection( im_transport_ptr transport, const tchar* name )
{
	return connection_ptr( new connection_type( *this, transport , 0 , false ) );
}

BOE_Pluggable_Messaging_Ptr Instance_IM::createMessaging()
{
	if( messaging_factory_ == 0 )
		BT_LOG_ERROR_THROW( getLogger(),
		toString() << BT_TEXT("> messaging_factory不能为空"), RuntimeException );
	return messaging_factory_->create();

}

void Instance_IM::setMessagingFactory( BOE_Pluggable_Messaging_Factory& factory )
{
	messaging_factory_ = &factory;
}

const tstring& Instance_IM::toString()
{
	return toString_;
}

void Instance_IM::setToString( const tstring& s )
{
	toString_ = s;
}

_im_end