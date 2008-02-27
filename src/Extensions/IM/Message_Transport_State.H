
#ifndef Message_Transport_State_H
#define Message_Transport_State_H

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

// Include files
#include "config_IM.h"
#include "BOE/Kernel/Kernel.H"
#include "BOE/IO/IO.h"
#include "Message_Transport_Handler.H"

/**
 */
_im_begin

class Transport_Read_State : public Transport_Protocol_State_T< Message_Transport_Handler >
{
public:
	static Transport_Read_State* get();

	int service( data_type& handle );

	Transport_Protocol_State* transition( data_type& data,
		im_transport_handler_type::read_result_type& result , void* act );
};


class Transport_Write_State : public Transport_Protocol_State_T< Message_Transport_Handler >
{
public:

	static Transport_Write_State* get();

	int service( data_type& handle );

	Transport_Protocol_State* transition( data_type& data,
		im_transport_handler_type::write_result_type& result , void* act );
	Transport_Protocol_State* transition( data_type& data,
		im_transport_handler_type::write_array_result_type& result , void* act );
	Transport_Protocol_State* transition( data_type& data,
		im_transport_handler_type::transmit_result_type& result , void* act );
};


class Transport_Close_State : public Transport_Protocol_State_T< Message_Transport_Handler >
{
public:

	static Transport_Close_State* get();

	int service( data_type& handle );
};

class Transport_Format_Error_State : public Transport_Protocol_State_T< Message_Transport_Handler >
{
public:

	static Transport_Format_Error_State* get();

	int service( data_type& handle );
};

_im_end

#endif // Message_Transport_State_H