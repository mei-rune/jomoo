
#ifndef Message_Transport_Connector_H
#define Message_Transport_Connector_H

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

// Include files
#include "config_IM.h"
#include "Message_Transport_Handler.H"
#include "Instance_IM.H"

/**
 */
_im_begin


class Message_Transport_Connector : public BOE_Connect_Handler
{
public:
	Message_Transport_Connector( Instance_IM& instance , const tstring& addr );
	~Message_Transport_Connector();
	
	int open( );
	void close( );

	void onConnect(BOE_Connect_Result& result);

	const tstring& toString() const;

private:
	BOE_Connector_Ptr connector_;
	Instance_IM& instance_;
	tstring addr_;
	tstring toString_;
};

typedef counter_ptr< Message_Transport_Connector > Message_Transport_Connector_Ptr;

_im_end

#endif // Message_Transport_Connector_H
