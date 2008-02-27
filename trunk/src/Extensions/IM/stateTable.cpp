#include "StdAfx.h"
#include "stateTable.H"
#include "BOE/exception.hpp"
#include "Message_Transport_State.H"

_im_begin

BOE_Export_C Transport_Protocol_State* _getState( u_int8_t v )
{
	switch( v )
	{
		case 'R' : return  Transport_Read_State::get();		// ����Ϣ
		case 'W' : return  Transport_Write_State::get();		// д��Ϣ
		case 'C' : return  Transport_Close_State::get();		// �ر�
		case 'E' : return  Transport_Format_Error_State::get();	//
	}
	return 0;
}

_im_end