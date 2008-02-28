
#include "StdAfx.h"
#include "framework/Singleton.h"
#include "serializer_factory.h"


_bt_serialize_begin

	//BTOUTSerializeFactory out;

BT_Export_C BTOUTSerializeFactory* ___BTOUTSerializeFactory_instance( )
{
	return /*&out;*/ BOE_Singleton< BTOUTSerializeFactory ,  BOE_Mutex >::instance( );
}

	//BTINPUTSerializeFactory input;


BT_Export_C BTINPUTSerializeFactory* ___BTINPUTSerializeFactory_instance( )
{
	return /*&input;*/ BOE_Singleton< BTINPUTSerializeFactory ,  BOE_Mutex >::instance();
}


_bt_serialize_end