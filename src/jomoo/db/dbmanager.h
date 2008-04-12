
#ifndef _DbManager_H_
#define _DbManager_H_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_db.h"
#include "DbConnection.H"
#include "DbExecute.H"
#include "DbQuery.H"
#include "include/BTNM_Export.hpp"

_jomoo_db_begin

class DbManager
{
public:
	virtual ~DbManager(){}
	virtual  PDbConnection createConnection( const tstring& name ) = 0;
};


class DbManager2
{
public:
	virtual ~DbManager2(){}
	virtual  PDbConnection2 createConnection( const tstring& name ) = 0;
};


#define ODBC_DRIVER "ODBC"
#define SQLITE_DRIVER "SQLITE"

BTNM_Export_C DbManager* ___DB_Init( const tchar* driver, const void* param );
BTNM_Export_C void ___DB_Fini( );
BTNM_Export_C DbManager* ___get_DbManager( );
BTNM_Export_C DbManager2* ___get_DbManager2( const char* driver );
BTNM_Export_C const char* ___get_DbDriver( );


BTNM_Export_C const char* ___get_Db( const char* tag );
BTNM_Export_C const char* ___get_DbTag( const char* tag );

_jomoo_db_end

#endif // _DbManager_H_