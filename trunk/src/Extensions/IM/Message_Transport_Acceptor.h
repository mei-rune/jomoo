
#ifndef Message_Transport_Acceptor_H
#define Message_Transport_Acceptor_H

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

class Message_Transport_Acceptor : public BOE_Accept_Handler
{
public:
	typedef counter_ptr < Message_Transport_Acceptor >  ptr_type;

	Message_Transport_Acceptor( Instance_IM& instance , const tstring& addr );
	~Message_Transport_Acceptor( );
	int open( );
	void close( );

	void onAccept( BOE_Accept_Result& result );

	const tstring& toString() const;
	
private:
	BOE_Acceptor_Ptr acceptor_;
	Instance_IM& instance_;
	tstring addr_;
	tstring toString_;
};

typedef Message_Transport_Acceptor::ptr_type Message_Transport_Acceptor_Ptr;

_im_end

#endif // Message_Transport_Acceptor_H
