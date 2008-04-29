
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

class DbDriver
{
public:
	virtual ~DbDriver(){}
	virtual  PDbConnection createConnection( const tstring& name ) = 0;
};

#define ODBC_DRIVER _T("ODBC")
#define SQLITE_DRIVER _T("SQLITE")

BTNM_Export_C DbDriver* ___get_DbDriver( const tchar* driver );



_jomoo_db_end

#endif // _DbManager_H_