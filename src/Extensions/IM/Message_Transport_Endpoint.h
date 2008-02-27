
#ifndef Message_Transport_Endpoint_H
#define Message_Transport_Endpoint_H

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

// Include files
#include "config_IM.h"
#include "Message_Transport_Acceptor.H"
#include "Message_Transport_Connector.H"

/**
 */
_im_begin


class Message_Transport_Endpoint
{
public:

	typedef Message_Transport_Acceptor acceptor_type;
	typedef Message_Transport_Acceptor_Ptr acceptor_ptr;
	typedef Message_Transport_Connector connector_type;
	typedef Message_Transport_Connector_Ptr connector_ptr;

	Message_Transport_Endpoint( Instance_IM& instance , const std::string & addr );

    const tstring& toString( ) const;

    connector_ptr connector( ) const;

    acceptor_ptr acceptor( ) const ;
private:

	Instance_IM& instance_;
	tstring addr_;
	tstring toString_;
	
};

typedef counter_ptr< Message_Transport_Endpoint > Message_Transport_Endpoint_Ptr;

_im_end

#endif // Message_Transport_Endpoint_H
