
#ifndef _DbManager_H_
#define _DbManager_H_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_db.h"
#include "jomoo/jomoo_export.h"
#include "DbConnection.H"
#include "DbCommand.H"
#include "DbQuery.H"

_jomoo_db_begin

class DbDriver
{
public:
	virtual ~DbDriver(){}
	virtual  DbConnection createConnection( const tstring& name ) = 0;
};

#define ODBC_DRIVER _T("ODBC")
#define SQLITE_DRIVER _T("SQLITE")

_jomoo_db_end

JOMOO_Export_C _jomoo_db DbDriver* ___get_DbDriver( const tchar* driver );

_jomoo_db_begin

DbDriver* get_DbDriver( const tchar* driver )
{
	return ___get_DbDriver( driver );
}

_jomoo_db_end

#endif // _DbManager_H_