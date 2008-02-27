
#ifndef Message_Transport_Data_H
#define Message_Transport_Data_H

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

// Include files
#include "config_IM.h"
#include "BOE/counter_ptr.hpp"
#include "BOE_Pluggable_Messaging.H"
#include "stateTable.H"

/**
 */
_im_begin

class Message_Transport_Data
{
public:
	typedef IMLoggerPtr LoggerPtr;

	virtual BOE_Pluggable_Messaging& getMessaging() = 0;

	virtual im_transport_type& getTransport() = 0;

	virtual stateTable& getJumpTable() = 0;

	virtual void nextState( Transport_Protocol_State* next ) = 0;

	virtual const tstring& toString() const = 0;

	virtual LoggerPtr getLogger() = 0;
};

_im_end

#endif // Message_Transport_Data_H