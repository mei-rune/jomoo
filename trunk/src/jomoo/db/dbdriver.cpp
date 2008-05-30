
#include <windows.h>
#include "DbDriver.H"
#include "DbConnection_ODBC.h"
#include "DbConnection_SQLITE.h"

#ifdef _MEMORY_DEBUG 
	#undef THIS_FILE
	#define new	   DEBUG_NEW  
	#define malloc DEBUG_MALLOC  
    static char THIS_FILE[] = __FILE__;  
#endif

_jomoo_db_begin

#ifdef HAS_ODBC_DRIVER

class DbDriver_ODBC : public DbDriver
{
public:
	DbConnection createConnection( const tstring& name );
private:
	tstring driver_;
};

DbConnection DbDriver_ODBC::createConnection( const tstring& name )
{
	return DbConnection( new spi::DbConnection_ODBC(name) );
}

#endif //HAS_ODBC_DRIVER


class DbDriver_SQLITE : public DbDriver
{
public:

	DbConnection createConnection( const tstring& name );
private:
	tstring driver_;
};

DbConnection DbDriver_SQLITE::createConnection( const tstring& name )
{
	return DbConnection( new spi::DbConnection_SQLITE(name) ); 
}

_jomoo_db_end

#ifdef HAS_ODBC_DRIVER
static _jomoo_db DbDriver_ODBC* g_DbDriver_ODBC = new _jomoo_db DbDriver_ODBC();
#endif
static _jomoo_db DbDriver_SQLITE* g_DbDriver_SQLITE = new _jomoo_db DbDriver_SQLITE();


JOMOO_Export_C _jomoo_db DbDriver* ___get_DbDriver( const tchar* driver )
{
#ifdef HAS_ODBC_DRIVER
	if( string_traits<tchar>::stricmp( driver, ODBC_DRIVER) == 0 )
		return g_DbDriver_ODBC;
#endif
	
	if( string_traits<tchar>::stricmp( driver, SQLITE_DRIVER) == 0 && ___init_sqlite( SQLITE_DLL ) )
		return g_DbDriver_SQLITE;
	
	return 0;
}