
#ifndef MessageServer_H
#define MessageServer_H

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

// Include files
#include "config_IM.h"
#include "BOE/IO/IO.h"
#include "Instance_IM.h"
#include "StateTable.H"
#include "BOE/Kernel/BOE_NULL_Concurrency.h"

typedef Transport_Protocol_State* (*Protocol_State_Point) ();

/**
 */
_im_begin


class MessageServer : public BOE_Server
{
public:

	typedef Instance_IM::LoggerPtr LoggerPtr;

	MessageServer( _io Instance_IO& instance );

	int open( _util PropertiesPtr config );
	void close( );

	LoggerPtr getLogger();
	const tstring& toString() const;
private:

	Instance_IM::acceptor_ptr pAcceptor_;
	Instance_IM instance_;
	stateTable manager_;
	tstring toString_;
	_kernel BOE_NULL_Concurrency concurrency_;
};

_im_end

#endif // MessageServer_H