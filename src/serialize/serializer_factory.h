
/**
 * -*- C++ -*-
 * -------------------------------------------------------------------------------
 * - °Ë®q°–®r ®q°–®r		        Serialize_Factory.h,v 1.0 2005/03/11 16:56:34
 *  ®u®ê®Ä®Ä®é ®q®q °–®r
 * ¶ÚÃÔ¶ÚÃÔÃÔ| ®t------
 * -------------------------------------------------------------------------------
 */

#ifndef _Serialize_Factory_H_
#define _Serialize_Factory_H_

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include "framework/Factory.h"
#include "bt_stream.h"
#include "config.h"
#include "serialize2.h"
#include "serialize_helper.h"
#include "reflection_impl.h"
#include "BT_Export.H"

_bt_serialize_begin

enum SERIALIZE_ENUM
{
	 dom_stream
	,bin_stream
	,array_stream
	,db_stream
};

class BTOUTSerializeFactory : public _bt Parameter_Factory< serialize_ostream_base , int , BIN_OUT_Source* >
{
public:
	BTOUTSerializeFactory(  )
		: _bt Parameter_Factory< serialize_ostream_base , int , BIN_OUT_Source* >( "BTOUTSerializeFactory" )
	{
	}
};

BT_Export_C BTOUTSerializeFactory* ___BTOUTSerializeFactory_instance( );


namespace BTOUTSerializeFactory_Singleton
{

	inline BTOUTSerializeFactory* instance( )
	{
		return ___BTOUTSerializeFactory_instance();
	}

	inline BTOUTSerializeFactory* get( )
	{
		return ___BTOUTSerializeFactory_instance();
	}

};


class BTINPUTSerializeFactory : public _bt Parameter_Factory< serialize_istream_base , int , BIN_INPUT_Source* >
{
public:
	BTINPUTSerializeFactory()
		: _bt Parameter_Factory< serialize_istream_base , int , BIN_INPUT_Source* >( "BTINPUTSerializeFactory" )
	{
	}

};

BT_Export_C BTINPUTSerializeFactory* ___BTINPUTSerializeFactory_instance( );

namespace BTINPUTSerializeFactory_Singleton
{

	inline BTINPUTSerializeFactory* instance( )
	{
		return ___BTINPUTSerializeFactory_instance();
	}

	inline BTINPUTSerializeFactory* get( )
	{
		return ___BTINPUTSerializeFactory_instance();
	}
};

_bt_serialize_end

#endif // _Serialize_Factory_H_