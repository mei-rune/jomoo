
#ifndef stateTable_H
#define stateTable_H

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

// Include files
#include "config_IM.h"
#include "Instance_IM.H"
#include "Transport_Protocol_State.H"

BOE_Export_C Transport_Protocol_State* _getState( u_int8_t v );

_im_begin



class stateTable
{
public:
	stateTable()
		: jumptable_( 256 , (Transport_Protocol_State*)0 )
	{
		jumptable_[ 'R'	] = _getState( 'R' );		// 读消息
		jumptable_[ 'W'	] = _getState( 'W' );		// 写消息
		jumptable_[ 'C'	] = _getState( 'C' );		// 关闭
		jumptable_[ 'E'	] = _getState( 'E' );	//
	}

	Transport_Protocol_State* operator[]( u_int8_t s)
	{
		return jumptable_[ s ];
	}

	void set( u_int8_t s , Transport_Protocol_State* state )
	{
		jumptable_[ s ] = state;
	}

	Transport_Protocol_State* get( u_int8_t s )
	{
		return jumptable_[ s ];
	}

private:
	 std::vector< Transport_Protocol_State* > jumptable_;
};

_im_end

#endif // stateTable_H

