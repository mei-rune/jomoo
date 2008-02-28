

/**
* -*- C++ -*-
* -------------------------------------------------------------------------------
* - °Ë®q°–®r ®q°–®r					 System_Directory.H,v 1.0 2005/05/17 16:41:54
*  ®u®ê®Ä®Ä®é ®q®q °–®r
* ¶ÚÃÔ¶ÚÃÔÃÔ| ®t------
* -------------------------------------------------------------------------------
*/

#ifndef _System_Directory_H_
#define _System_Directory_H_

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include "config.h"
#include <Windows.h>

_bt_begin

DWORD inline GetAppPath(char *szModName, DWORD Size)
{
	DWORD ps = GetModuleFileName(NULL, szModName, Size);
	while(ps > 0 && szModName[ps-1] != '\\') ps--;
	szModName[ps] = '\0';
	return ps;
}

std::string inline GetAppPath( )
{
	char path[ MAX_PATH ] = "";
	GetAppPath( path, MAX_PATH  );
	return std::string( path );
}
_bt_end

#endif // _System_Directory_H_