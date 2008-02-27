#include "StdAfx.h"
#include "Message_Transport_State.H"
#include "BOE/get_last_error.H"


#ifdef _MEMORY_DEBUG
#undef THIS_FILE
#define new	   DEBUG_NEW  
#define malloc DEBUG_MALLOC  
static char THIS_FILE[] = __FILE__;  
#endif // _MEMORY_DEBUG

_im_begin



Transport_Read_State* Transport_Read_State::get()
{
	static Transport_Read_State state;
	return &state;
}

int Transport_Read_State::service( data_type& data )
{
	if( data.getTransport().read(
		data
		,data.getMessaging().wd_ptr()
		, data.getMessaging().wd_space()
		, 0
		) )
		return 0;
	BT_LOG_ERROR( data.getLogger(), data.toString()
		<< BT_TEXT("读数据时发生错误,") << get_last_error() );
	data.nextState( data.getJumpTable().get( 'C' ) );
	return 0;
}

Transport_Protocol_State* Transport_Read_State::transition( data_type& data,
														   im_transport_handler_type::read_result_type& result , void* act )
{
	if( ! result.success() )
	{
		if( result.error() == ERROR_OPERATION_ABORTED )
		{
			if( data.isStop() )
			{
				BT_LOG_ERROR( data.getLogger(), data.toString()
					<< BT_TEXT("被中断，系统停止") );
				return data.getJumpTable().get( 'C' );
			}
			data.getMessaging().wd_ptr( result.bytes_to_transferred() );
			int r = data.getMessaging().parse( );
			BT_LOG_ERROR( data.getLogger(), data.toString()
				<< BT_TEXT("被中断开始写数据") );
			return data.getJumpTable().get( 'W' );
		}

		BT_LOG_ERROR( data.getLogger(), data.toString()
			<< BT_TEXT("读数据时发生错误,") << get_last_error() );
		return data.getJumpTable().get( 'C' );
	}

	data.getMessaging().wd_ptr( result.bytes_to_transferred() );
	int r = data.getMessaging().parse( );
	if( r == 0 )
	{
		if( !data.getMessaging().hasData() )
			return data.getJumpTable().get( 'W' );
		// 消息没有读完
		return data.getJumpTable().get( 'R' );
	}
	else if( r > 0 )
	{
		if( !data.getMessaging().hasData() )
			return data.getJumpTable().get( 'W' );

		//BT_LOG_INFO( data.getLogger(), data.toString()
		//	<< BT_TEXT("读数据完成,下一步开始处理消息") );
		// 读数完成
		// 读完消息了
		return data.getJumpTable().get( 'R' ); //data.state( processing )
	}
	else
	{
		BT_LOG_INFO( data.getLogger(), data.toString()
			<< BT_TEXT("读数据时,发现数据格式不正确") );

		// 消息格式不对
		return data.getJumpTable().get( 'E' );
		//return  Transport_Format_Error_State::get();
	}
}

Transport_Write_State* Transport_Write_State::get( )
{
	static Transport_Write_State state;
	return &state;
}

int Transport_Write_State::service( data_type& data )
{
	bool r = false;
	switch( data.getMessaging().rd_type() )
	{
	case 1:
		r = data.getTransport().write(
			data 
			, data.getMessaging().rd_ptr()
			, data.getMessaging().rd_length()
			, 0 ) ;
		break;
	case 2:
		r = data.getTransport().write(
			data
			, data.getMessaging().rd_vec()
			, data.getMessaging().rd_size()
			, 0 ) ;
		break;
	case 3:
		r = data.getTransport().transmit(
			data
			, data.getMessaging().rd_f_vec()
			, data.getMessaging().rd_f_size()
			, 0 ) ;
		break;
	default:
		BT_LOG_ERROR( data.getLogger(), data.toString()
			<< BT_TEXT("写数据时发生错误,不正确的数据类型") );
		data.nextState( data.getJumpTable().get( 'C' ) );
		return 0;
	};

	if( r )
		return 0;

	BT_LOG_ERROR( data.getLogger(), data.toString()
		<< BT_TEXT("写数据时发生错误,") << get_last_error() );
	data.nextState( data.getJumpTable().get( 'C' ) );
	return 0;
}

Transport_Protocol_State* Transport_Write_State::transition( 
	data_type& data,
	im_transport_handler_type::write_result_type& result , void* act )
{
	if( ! result.success() )
	{
		if( result.error() != ERROR_OPERATION_ABORTED )
		{
			BT_LOG_ERROR( data.getLogger(), data.toString()
				<< BT_TEXT("写数据时发生错误,") << get_last_error() );
			return data.getJumpTable().get( 'C' );
		}else if( data.isStop() )
		{
			BT_LOG_ERROR( data.getLogger(), data.toString()
				<< BT_TEXT("写数据时被中断，系统停止") );
			return data.getJumpTable().get( 'C' );
		}
		BT_LOG_ERROR( data.getLogger(), data.toString()
			<< BT_TEXT("写数据时被意外中断") );
		return data.getJumpTable().get( 'C' );
	}

	data.getMessaging().rd_ptr( result.bytes_to_transferred() );
	if( !data.getMessaging().hasData() )
	{
		BT_LOG_INFO( data.getLogger(), data.toString()
			<< BT_TEXT("写数据完成,下一步开始读数据") );
		return data.getJumpTable().get( 'R' );
	}
	return data.getJumpTable().get( 'W' );
}


Transport_Protocol_State* Transport_Write_State::transition( 
	data_type& data,
	im_transport_handler_type::write_array_result_type& result , void* act )
{
	if( ! result.success() )
	{
		if( result.error() != ERROR_OPERATION_ABORTED )
		{
			BT_LOG_ERROR( data.getLogger(), data.toString()
				<< BT_TEXT("写数据时发生错误,") << get_last_error() );
			return data.getJumpTable().get( 'C' );
		}else if( data.isStop() )
		{
			BT_LOG_ERROR( data.getLogger(), data.toString()
				<< BT_TEXT("写数据时被中断，系统停止") );
			return data.getJumpTable().get( 'C' );
		}
		BT_LOG_ERROR( data.getLogger(), data.toString()
			<< BT_TEXT("写数据时被意外中断") );
		return data.getJumpTable().get( 'C' );
	}

	data.getMessaging().rd_vec( result.bytes_to_transferred() );
	if( !data.getMessaging().hasData() )
	{
		BT_LOG_INFO( data.getLogger(), data.toString()
			<< BT_TEXT("写数据完成,下一步开始读数据") );
		return data.getJumpTable().get( 'R' );
	}

	return data.getJumpTable().get( 'W' );
}

Transport_Protocol_State* Transport_Write_State::transition( 
	data_type& data,
	im_transport_handler_type::transmit_result_type & result , void* act )
{
	if( ! result.success() )
	{
		if( result.error() != ERROR_OPERATION_ABORTED )
		{
			BT_LOG_ERROR( data.getLogger(), data.toString()
				<< BT_TEXT("写数据时发生错误,") << get_last_error() );
			return data.getJumpTable().get( 'C' );
		}else if( data.isStop() )
		{
			BT_LOG_ERROR( data.getLogger(), data.toString()
				<< BT_TEXT("写数据时被中断，系统停止") );
			return data.getJumpTable().get( 'C' );
		}
		BT_LOG_ERROR( data.getLogger(), data.toString()
			<< BT_TEXT("写数据时被意外中断") );
		return data.getJumpTable().get( 'C' );
	}

	data.getMessaging().rd_f_vec( result.bytes_to_transferred() );
	if( !data.getMessaging().hasData() )
	{
		BT_LOG_INFO( data.getLogger(), data.toString()
			<< BT_TEXT("写数据完成,下一步开始读数据") );
		return data.getJumpTable().get( 'R' );
	}

	return data.getJumpTable().get( 'W' );
}

Transport_Close_State* Transport_Close_State::get()
{
	static Transport_Close_State state;
	return &state;
}

int Transport_Close_State::service( data_type& handle )
{
	return -1;
}

Transport_Format_Error_State* Transport_Format_Error_State::get()
{
	static Transport_Format_Error_State state;
	return &state;
}

int Transport_Format_Error_State::service( data_type& handle )
{
	return -1;
}

_im_end