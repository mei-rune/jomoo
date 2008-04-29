
#include <windows.h>
#include "DbDriver.H"
#include "DbConnection_ODBC.h"
#include "DbConnection_SQLITE.h"

#include "include/config.h"
#ifdef _MEMORY_DEBUG 
	#undef THIS_FILE
	#define new	   DEBUG_NEW  
	#define malloc DEBUG_MALLOC  
    static char THIS_FILE[] = __FILE__;  
#endif




_jomoo_db_begin

class DbDriver_ODBC : public DbDriver
{
public:
	PDbConnection createConnection( const tstring& name );
private:
	tstring driver_;
};

PDbConnection DbDriver_ODBC::createConnection( const tstring& name )
{
	return PDbConnection( new DbConnection_ODBC(name) );
}


class DbDriver_SQLITE : public DbDriver
{
public:

	PDbConnection createConnection( const tstring& name );
private:
	tstring driver_;
};

PDbConnection DbDriver_SQLITE::createConnection( const tstring& name )
{
	return PDbConnection( new DbConnection_SQLITE(name) ); 
}

static DbDriver_ODBC* g_DbDriver_ODBC = new DbDriver_ODBC();
static DbDriver_SQLITE* g_DbDriver_SQLITE = new DbDriver_SQLITE();


BTNM_Export_C DbDriver* ___get_DbDriver( const tchar* driver )
{
	if( tstrcasencmp( driver, ODBC_DRIVER) == 0 )
		return g_DbDriver_ODBC;
	else if( tstrcasencmp( driver, SQLITE_DRIVER) == 0 && ___init_sqlite() )
		return g_DbDriver_SQLITE;
	else
		return 0;
}

_jomoo_db_end