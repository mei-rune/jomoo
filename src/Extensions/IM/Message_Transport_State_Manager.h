
#ifndef Message_Transport_State_Manager_H
#define Message_Transport_State_Manager_H

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

// Include files
#include "config_IM.h"
#include "Instance_IM.H"
#include "Transport_Protocol_State.H"


_im_begin

class Message_Transport_State_Manager : public std::vector< Transport_Protocol_State* >
{
public:

	enum Protocol_State
	{
		  reading			// 读消息
		, writeing			// 写消息
		, closing			// 关闭
		, format_error		//
	};

	Message_Transport_State_Manager();

};

_im_end

#endif // Message_Transport_State_Manager_H

