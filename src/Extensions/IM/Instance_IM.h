

#ifndef Instance_IM_H
#define Instance_IM_H

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

// Include files
#include "config_IM.h"
#include "BOE/Logger.H"
#include "BOE/IO/Instance_IO.h"
#include "BOE/Kernel/Kernel.H"
#include "BOE/counter_ptr.hpp"
#include "Transport_Protocol_State.H"
#include "BOE_Pluggable_Messaging.H"

_im_begin

class Message_Transport_Endpoint;
typedef counter_ptr< Message_Transport_Endpoint > Message_Transport_Endpoint_Ptr;

class Message_Transport_Acceptor;
typedef counter_ptr< Message_Transport_Acceptor > Message_Transport_Acceptor_Ptr;

class Message_Transport_Connector;
typedef counter_ptr< Message_Transport_Connector > Message_Transport_Connector_Ptr;

class BOE_Pluggable_Messaging;
typedef counter_ptr< BOE_Pluggable_Messaging > BOE_Pluggable_Messaging_Ptr;

class Message_Transport_Handler;
typedef intrusive_ptr<Message_Transport_Handler> Message_Transport_Handler_Ptr;

class Instance_IM
{
public:

	struct DefaultsAndOverrides
	{
		DefaultsAndOverrides()
			: maxMessageSize( 4 * 1024 )
		{
		}
		size_t maxMessageSize; // 64 * 1024
	};

	typedef Instance_IO::LoggerPtr LoggerPtr;


	typedef Message_Transport_Endpoint endpoint_type;
	typedef Message_Transport_Endpoint_Ptr endpoint_ptr;
	typedef Message_Transport_Acceptor acceptor_type;
	typedef Message_Transport_Acceptor_Ptr acceptor_ptr;
	typedef Message_Transport_Connector connector_type;
	typedef Message_Transport_Connector_Ptr connector_ptr;

	typedef Message_Transport_Handler connection_type;
	typedef Message_Transport_Handler_Ptr connection_ptr;

	Instance_IM( _io Instance_IO& instance );
	
	~Instance_IM(void);

	int open( _util PropertiesPtr config );

	void close( );

	bool isStop();

	_io Instance_IO& getIOInstance();

	const DefaultsAndOverrides& getDefaultsAndOverrides()const;

	void setConcurrencyBridge( _kernel BOE_Concurrency_Impl& concurrency );
	_kernel BOE_Concurrency_Impl& getConcurrencyBridge();

	endpoint_ptr createEndpoint( const tstring& addr );

	acceptor_ptr createAcceptor( const tstring& addr );

	connector_ptr createConnector( const tstring& addr );

	connection_ptr createConnection( im_transport_ptr transport, const tchar* name = 0 );

	BOE_Pluggable_Messaging_Ptr createMessaging();
	void setMessagingFactory( BOE_Pluggable_Messaging_Factory& factory );

	
	LoggerPtr getLogger();

	void setLogger( LoggerPtr );

	const tstring& toString();
	void setToString( const tstring& s );

private:

	DECLARE_NO_COPY_CLASS( Instance_IM );

	_io Instance_IO& ioinstance_;

	BOE_Pluggable_Messaging_Factory* messaging_factory_;
	_kernel BOE_Concurrency_Impl* concurrency_;

	DefaultsAndOverrides overrides_;

	tstring toString_;

};

typedef counter_ptr< Instance_IM > IMInstancePtr;

_im_end

#endif // Instance_IM_H