#include "StdAfx.h"
#include "Message_Transport_State_Manager.H"
#include "BOE/exception.hpp"
#include "Message_Transport_State.H"

_im_begin

Message_Transport_State_Manager::Message_Transport_State_Manager()
{
	resize( reading,0 );
	(*this)[ reading	] = Transport_Read_State::get();		// 读消息
	resize( writeing,0 );
	(*this)[ Message_Transport_State_Manager::writeing	] = Transport_Write_State::get();		// 写消息
	resize( closing,0 );
	(*this)[ Message_Transport_State_Manager::closing	] = Transport_Close_State::get();		// 关闭
	resize( format_error,0 );
	(*this)[ Message_Transport_State_Manager::format_error	] = Transport_Format_Error_State::get();	//
}

_im_end