
#ifndef Router_Server_H
#define Router_Server_H

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_IM.h"
#include "../Instance_IM.H"
#include "../MsgEndPoint.H"
#include "../ConnectionManager.H"
#include "BOE/Kernel/Kernel.h"
#include "Router_Protocol.H"
#include <memory>

_im_begin

class Router_Server : public BOE_Server
{
public:
	typedef Instance_IM instance_type;

	Router_Server( _io Instance_IO& instance );
	int open( _util PropertiesPtr config );
	void close( );
	const tstring& toString() const;

	ConnectionManager< Router_Handler >& manager();
	Router_Handler_Ptr createHandler( );
	instance_type::acceptor_ptr acceptor();
private:
	Instance_IM instance_;
	ConnectionManager< Router_Handler > manager_;
	instance_type::acceptor_ptr acceptor_;
	std::auto_ptr< Router_Accept_Handler > handler_;
	tstring toString_;
	
};

_im_end

#endif // Router_Server_H