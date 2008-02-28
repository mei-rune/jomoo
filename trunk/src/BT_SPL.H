

/**
* -*- C++ -*-
* -------------------------------------------------------------------------------
* - °Ë®q°–®r ®q°–®r							   BT_SPL.H,v 1.0 2005/03/25 10:50:54
*  ®u®ê®Ä®Ä®é ®q®q °–®r
* ¶ÚÃÔ¶ÚÃÔÃÔ| ®t------
* -------------------------------------------------------------------------------
*/

#ifndef _BT_SPL_H_
#define _BT_SPL_H_


#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include "util/System_Directory.H"
#include "util/BOE_Log_Base.H"
#include "util/BT_Memory_Base.H"
#include "util/BT_Configure_Base.H"

#ifndef NO_DB
#include "db/DataBase_Manager.H"
#endif // NO_DB

_bt_begin


_bt_end

BT_Export_C int ___init_spl(  );
BT_Export_C void ___fini_spl( );

#ifndef _NO_BT_SPL_LIB_

#pragma comment( lib ,"bt_spl.lib" )

#endif // _NO_TOP_LIB_

#endif // _BT_SPL_H_