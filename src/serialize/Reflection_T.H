
/**
 * -*- C++ -*-
 * -------------------------------------------------------------------------------
 * - ¤╭⌒╮ ╭⌒╮		              Reflection_T.h,v 1.0 2005/03/14 14:21:34
 *  ╱◥██◣ ╭╭ ⌒╮
 * ︱田︱田田| ╰------
 * -------------------------------------------------------------------------------
 */

#ifndef _Reflection_T_H_
#define _Reflection_T_H_

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include "serializer_factory.h"

#define Reflection_T_ST_1 typename T
#define Reflection_T_ST_2 T


template< Reflection_T_ST_1 >
class Reflection_T
{
public:
	Reflection_T( const char* file_name ,int type = dom_stream )
	{
		if( file_name == 0 )
			throw( std::runtime_error( "文件名不可以为空" ) );
		_bt_serialize BIN_INPUT_Source in( file_name );
		dsr.reset( _bt_serialize BTINPUTSerializeFactory_Singleton::instance()->CreateObject( type ,&in  ) );
		if( dsr.get() == 0 )
			throw( std::runtime_error( "创建流失败" ) ) ;
	}

	Reflection_T( const void * buf, size_t lenght ,int type = dom_stream )
	{
		if( buf == 0 )
			throw( std::runtime_error( "内存不可以为空" ) );
		_bt_serialize BIN_INPUT_Source in( buf,lenght );
		dsr.reset( _bt_serialize BTINPUTSerializeFactory_Singleton::instance()->CreateObject( type ,&in  ) );
		if( dsr.get() == 0 )
			throw( std::runtime_error( "创建流失败" ) ) ;
	}

	Reflection_T( bt_istream& istream ,int type = dom_stream )
	{
		_bt_serialize BIN_INPUT_Source in( &istream );
		dsr.reset( _bt_serialize BTINPUTSerializeFactory_Singleton::instance()->CreateObject( type ,&in  ) );
		if( dsr.get() == 0 )
			throw( std::runtime_error( "创建流失败" ) ) ;
	}

	Reflection_T( BIN_INPUT_Source bos ,int type = dom_stream )
	{
		_bt_serialize BIN_INPUT_Source in( bos );
		dsr.reset( _bt_serialize BTINPUTSerializeFactory_Singleton::instance()->CreateObject( _bt_serialize dom_stream ,&in  ) );
		if( dsr.get() == 0 )
			throw( std::runtime_error( "创建流失败" ) ) ;
	}

	Reflection_T( bt_i_stream_base* stream )
	: dsr( stream )
	{
		if( dsr.get() == 0 )
			throw( std::runtime_error( "创建流失败" ) ) ;
	}
};


#endif // _Reflection_T_H_