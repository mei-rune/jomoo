#include "StdAfx.h"
#include "Instance_Proxy.h"
#include "BOE/exception.hpp"
#include <queue>

#ifdef _MEMORY_DEBUG
#undef THIS_FILE
#define new	   DEBUG_NEW  
#define malloc DEBUG_MALLOC  
static char THIS_FILE[] = __FILE__;  
#endif // _MEMORY_DEBUG

_proxy_begin

Instance_Proxy::Instance_Proxy( _io Instance_IO& ioinstance )
: ioinstance_( ioinstance )
, concurrency_( 0 )
, toString_( BT_TEXT("Instance_Proxy") )
{
}

Instance_Proxy::~Instance_Proxy(void)
{
	close();
}

int Instance_Proxy::open( _util PropertiesPtr config )
{
	//overrides_.maxMessageSize = config->getPropertyAsIntWithDefault( "BOE.Proxy.maxMessageSize", 1024 * 6 );
	return 0;
}

void Instance_Proxy::close( )
{
	//ioinstance_.close( );
}

bool Instance_Proxy::isStop()
{
	return ioinstance_.isStop();
}

Instance_Proxy::LoggerPtr Instance_Proxy::getLogger()
{
	return ioinstance_.getLogger();
}

void Instance_Proxy::setLogger( LoggerPtr ptr )
{
	ioinstance_.setLogger( ptr );
}

Instance_IO& Instance_Proxy::getIOInstance()
{
	return ioinstance_;
}

const Instance_Proxy::DefaultsAndOverrides& Instance_Proxy::getDefaultsAndOverrides()const
{
	return overrides_;
}

void Instance_Proxy::setConcurrencyBridge( _kernel BOE_Concurrency_Impl& concurrency )
{
	concurrency_ = &concurrency;
}

BOE_Concurrency_Impl& Instance_Proxy::getConcurrencyBridge()
{
	if( concurrency_ == 0 )
		BT_LOG_ERROR_THROW( getLogger(),
		toString() << BT_TEXT("> ConcurrencyBridge²»ÄÜÎª¿Õ"), RuntimeException );
	return *concurrency_;
}

const tstring& Instance_Proxy::toString()
{
	return toString_;
}

void Instance_Proxy::setToString( const tstring& s )
{
	toString_ = s;
}

_proxy_end