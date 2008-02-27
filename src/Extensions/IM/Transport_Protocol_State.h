
#ifndef Transport_Protocol_State_H
#define Transport_Protocol_State_H

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

// Include files
#include "config_IM.h"
#include "BOE/Kernel/Kernel.H"
#include "BOE/IO/IO.h"

/**
 */
_im_begin

typedef BOE_Transport_Handler im_transport_handler_type;
typedef im_transport_handler_type::ptr_type im_transport_handler_ptr;
typedef BOE_Transport im_transport_type;
typedef im_transport_type::ptr_type im_transport_ptr;

class Transport_Protocol_State
{
public:
	
	virtual ~Transport_Protocol_State(){}

	virtual int service( void* data ) = 0;

	virtual Transport_Protocol_State* transition(  void* data, im_transport_handler_type::read_result_type& result , void* act ) = 0;

	virtual Transport_Protocol_State* transition(  void* data, im_transport_handler_type::read_array_result_type& result , void* act ) = 0;

	virtual Transport_Protocol_State* transition(  void* data, im_transport_handler_type::write_result_type& result , void* act ) = 0;

	virtual Transport_Protocol_State* transition(  void* data, im_transport_handler_type::write_array_result_type& result , void* act ) = 0;

	virtual Transport_Protocol_State* transition(  void* data, im_transport_handler_type::transmit_result_type& result , void* act ) = 0;
};

template< typename D >
class Transport_Protocol_State_T : public Transport_Protocol_State
{
public:
	typedef D data_type;

	virtual ~Transport_Protocol_State_T(){}

	virtual int service( void* data )
	{
		return service( *( D*) data );
	}

	virtual Transport_Protocol_State* transition( void* data, typename im_transport_handler_type::read_result_type& result , void* act )
	{
		return transition( *( D*) data ,result, act );
	}

	virtual Transport_Protocol_State* transition( void* data, typename im_transport_handler_type::read_array_result_type& result , void* act )
	{
		return transition( *( D*) data ,result, act );
	}

	virtual Transport_Protocol_State* transition( void* data, typename im_transport_handler_type::write_result_type& result , void* act )
	{
		return transition( *( D*) data ,result, act );
	}

	virtual Transport_Protocol_State* transition( void* data, typename im_transport_handler_type::write_array_result_type& result , void* act )
	{
		return transition( *( D*) data ,result, act );
	}

	virtual Transport_Protocol_State* transition( void* data, typename im_transport_handler_type::transmit_result_type& result , void* act )
	{
		return transition( *( D*) data ,result, act );
	}

	virtual int service( D& handle )
	{
		BT_LOG_ERROR( handle.getLogger(), handle.toString() << BT_TEXT("> 未定义的操作")  );
		return -1;
	}

	virtual Transport_Protocol_State* transition( D& data, typename im_transport_handler_type::read_result_type& result , void* act )
	{
		BT_LOG_ERROR( data.getLogger(), data.toString() << BT_TEXT("> 未知的读结果")  );
		return 0;
	}

	virtual Transport_Protocol_State* transition( D& data, typename im_transport_handler_type::read_array_result_type& result , void* act )
	{
		BT_LOG_ERROR( data.getLogger(), data.toString() << BT_TEXT("> 未知的读数组结果")  );
		return 0;
	}

	virtual Transport_Protocol_State* transition( D& data, typename im_transport_handler_type::write_result_type& result , void* act )
	{
		BT_LOG_ERROR( data.getLogger(), data.toString() << BT_TEXT("> 未知的写结果")  );
		return 0;
	}

	virtual Transport_Protocol_State* transition( D& data, typename im_transport_handler_type::write_array_result_type& result , void* act )
	{
		BT_LOG_ERROR( data.getLogger(), data.toString() << BT_TEXT("> 未知的写数组结果")  );
		return 0;
	}

	virtual Transport_Protocol_State* transition( D& data, typename im_transport_handler_type::transmit_result_type& result , void* act )
	{
		BT_LOG_ERROR( data.getLogger(), data.toString() << BT_TEXT("> 未知的传输结果")  );
		return 0;
	}
};

_im_end

#endif // Transport_Protocol_State_H