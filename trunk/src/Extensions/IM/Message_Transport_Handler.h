
#ifndef Message_Transport_Protocol_H
#define Message_Transport_Protocol_H

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

// Include files
#include "config_IM.h"
#include "Message_Transport_Data.H"
#include "Instance_IM.H"

/**
 */
_im_begin

class Message_Transport_Handler : public im_transport_handler_type
									, public BOE_Protocol_Handler
									, public Message_Transport_Data
{
public:

	typedef intrusive_ptr<Message_Transport_Handler> ptr_type;

	typedef Message_Transport_Data::LoggerPtr LoggerPtr;

	Message_Transport_Handler( Instance_IM& instance
		, im_transport_ptr transport
		, stateTable* pJumpTable
		, bool delete_table );

	int open( );

	void close( );

	bool isStop();

	void finalize();

	int service();

	void onRead( im_transport_handler_type::read_result_type& result);

	void onReadArray( im_transport_handler_type::read_array_result_type& result ) ;

	void onWrite( im_transport_handler_type::write_result_type& result) ;

	void onWriteArray( im_transport_handler_type::write_array_result_type& result) ;

	void onTransmit( im_transport_handler_type::transmit_result_type& result ) ;

	BOE_Pluggable_Messaging& getMessaging();

	im_transport_type& getTransport();
	void setTransportHandler( im_transport_handler_type& handle );
	im_transport_handler_type& getTransportHandler(  );
	
	const tstring& toString() const;
	LoggerPtr getLogger();

	Instance_IM& instance();

	stateTable& getJumpTable();
	void nextState( Transport_Protocol_State* next );

	DECLARE_SHARED();

private:

	DECLARE_NO_COPY_CLASS( Message_Transport_Handler );

	Instance_IM& instance_;
	Transport_Protocol_State* state_;

	BOE_Pluggable_Messaging_Ptr Messaging_;

	im_transport_ptr transport_;

	std::auto_ptr< stateTable > selfTable_;
	stateTable* pJumpTable_;

	tstring toString_;
};

typedef Message_Transport_Handler::ptr_type Message_Transport_Handler_Ptr;

_im_end

#endif // Message_Transport_Protocol_H