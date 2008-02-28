// BT_SPL.cpp : 定义 DLL 应用程序的入口点。
//

#include "stdafx.h"
#include "BT_Export.H"

//BOOL APIENTRY DllMain( HANDLE hModule, 
//                       DWORD  ul_reason_for_call, 
//                       LPVOID lpReserved
//					 )
//{
//    return TRUE;
//}

//#include "util/BT_Configure_XML.H"
#include "util/BT_Log_CPlus.H"
#include "util/BT_Log_Cxx.H"
#include "util/System_Directory.H"
#include "BT_SPL.H"

_bt_begin


typedef BOE_Log_NDC_Base* (* make_BT_NDC_t)( );
make_BT_NDC_t make_BT_NDC_ = NULL;

typedef BOE_Log_Impl* (* make_BOE_LOG_t)( const tchar* name );
make_BOE_LOG_t make_BOE_Log_ = NULL;

_bt_end

//BT_Export_C int ___init_spl( )
//{
//#ifndef _NO_LOGCPLUS_
//	_bt make_BT_NDC_ = _bt make_BT_NDC_CPlus;
//	_bt make_BOE_Log_ = _bt make_BT_Log_CPlus;
//#endif //  _NO_LOGCPLUS_
//
//#ifndef NOLOG4CXX
//	_bt make_BT_NDC_ = _bt make_BT_NDC_Cxx;
//	_bt make_BOE_Log_ = _bt make_BT_Log_Cxx;
//#endif //  _NO_LOGCPLUS_
//
//#ifndef NO_DB
//	_bt ___DB_Init( SQLITE_DRIVER ,0);
//#endif //  NO_DB
//
//	return 0;
//}
//
//
//BT_Export_C void ___fini_spl( )
//{
//#ifndef NO_DB
//	_bt  ___DB_Fini( );
//#endif //  NO_DB
//}

namespace LOG
{

BT_Export_C _bt BOE_Log_NDC_Base* ___make_BOE_NDC( )
{
#ifndef NOLOG4CXX
	return  _bt make_BT_NDC_Cxx();
#elif defined ( _NO_LOGCPLUS_ )
	return  _bt make_BT_NDC_CPlus();
#elif
	return 0;
#endif //
}

BT_Export_C _bt BOE_Log_Impl* ___make_BOE_Log( const tchar* name  )
{
#ifndef NOLOG4CXX
	return _bt make_BT_Log_Cxx( name );
#elif defined ( _NO_LOGCPLUS_ )
	return _bt make_BT_Log_CPlus( name );
#elif
	return 0;
#endif //
}

BT_Export_C int ___init_log( )
{
#ifndef NOLOG4CXX
	return _bt init_BT_Log_Cxx(  );
#elif defined ( _NO_LOGCPLUS_ )
	return _bt init_BT_Log_CPlus(  );
#elif
	return 0;
#endif //
}

BT_Export_C void ___shutdown_log( )
{
#ifndef NOLOG4CXX
	return _bt shutdown_BT_Log_Cxx(  );
#elif defined ( _NO_LOGCPLUS_ )
	return _bt shutdown_BT_Log_CPlus(  );
#elif
	return 0;
#endif //
}

}