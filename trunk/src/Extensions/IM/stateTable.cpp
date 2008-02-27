#include "StdAfx.h"
#include "stateTable.H"
#include "BOE/exception.hpp"
#include "Message_Transport_State.H"

_im_begin

BOE_Export_C Transport_Protocol_State* _getState( u_int8_t v )
{
	switch( v )
	{
		case 'R' : return  Transport_Read_State::get();		// 读消息
		case 'W' : return  Transport_Write_State::get();		// 写消息
		case 'C' : return  Transport_Close_State::get();		// 关闭
		case 'E' : return  Transport_Format_Error_State::get();	//
	}
	return 0;
}

_im_end