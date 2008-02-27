
#ifndef BOE_Buffer_T_H
#define BOE_Buffer_T_H

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_IM.h"
#include "../Instance_IM.H"
#include "../Msgconnection.H"
#include "BOE/Kernel/Kernel.h"


_im_begin

class Router_Handler : public BOE_Protocol_Handler
							, public Msg_Connection_Handler
{
public:

	virtual void onMessage( ) = 0;
	virtual void onPresent( ) = 0;
	virtual void onIQ( ) = 0;
	virtual void onX( ) = 0;
	virtual void onError() = 0;

private:

	Msg_Connection_Ptr connection_;
};

_im_end

#endif // BOE_Buffer_T_H