
#ifndef Router_Protocol_H
#define Router_Protocol_H

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_IM.h"
#include "../Instance_IM.H"
#include "../MsgEndPoint.H"
#include "BOE/Kernel/Kernel.h"
#include "../Message.h"
#include <list>
_im_begin

class Router_Server;

class Router_Session : public Message_Read_Handler
	: public Message_Transport_Handler
{
public:

	Router_Session( Router_Server& server );

	open( )

	LoggerPtr getLogger();
	const tstring& toString() const;

private:
	bool running_;

	Router_Server& server_;
	Msg_Connection_Ptr connection_;
	tstring username_;
	tstring toString_;
	std::list< Message_Ptr > packets_;
	Message_Ptr read_packet_;
};



class Router_Accept_Handler : public Msg_Accept_Handler
{
public:
	Router_Accept_Handler( Router_Server& server );
	void onAccept( Msg_Accept_Result& result );
private:
	Router_Server& server_;
};

typedef Router_Handler::connection_ptr Router_Handler_Ptr;
typedef counter_ptr< Router_Accept_Handler > Router_Accept_Handler_Ptr;
_im_end

#endif // Router_Protocol_H