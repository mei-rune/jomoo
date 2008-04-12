
#include <windows.h>
#include "DbManager.H"
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

class DbManager_ODBC : public DbManager
{
public:
	PDbConnection createConnection( const tstring& name );
private:
	tstring driver_;
};

PDbConnection DbManager_ODBC::createConnection( const tstring& name )
{
	return PDbConnection( new DbConnection_ODBC(name) );
}


class DbManager_ODBC2 : public DbManager2
{
public:
	PDbConnection2 createConnection( const tstring& name );
private:
	tstring driver_;
};

PDbConnection2 DbManager_ODBC2::createConnection( const tstring& name )
{
	return PDbConnection2( new DbConnection_ODBC(name) );
}


class DbManager_SQLITE : public DbManager
{
public:


	PDbConnection createConnection( const tstring& name );

private:

	tstring driver_;

};

PDbConnection DbManager_SQLITE::createConnection( const tstring& name )
{
	return PDbConnection( new DbConnection_SQLITE(name) ); 
}

class DbManager_SQLITE2 : public DbManager2
{
public:


	PDbConnection2 createConnection( const tstring& name );

private:

	tstring driver_;

};

PDbConnection2 DbManager_SQLITE2::createConnection( const tstring& name )
{
	return PDbConnection2( new DbConnection_SQLITE(name) ); 
}

static DbManager* g_DbManager = 0;
static DbManager2* g_DbManager2_ODBC = 0;
static DbManager2* g_DbManager2_SQLITE = 0;
static tstring g_DbDriver;

BTNM_Export_C DbManager* ___DB_Init( const tchar* driver, const void* param )
{
	if( driver == 0 )
		return 0;

	g_DbDriver = driver;

	if( tstrcasencmp( driver, ODBC_DRIVER) == 0 )
		g_DbManager = new DbManager_ODBC();
	else if( tstrcasencmp( driver, SQLITE_DRIVER) == 0 && ___init_sqlite() )
		g_DbManager = new DbManager_SQLITE();
	else
		return 0;

	g_DbManager2_ODBC = new DbManager_ODBC2();
	g_DbManager2_SQLITE = new DbManager_SQLITE2();

	return g_DbManager;
}

BTNM_Export_C void ___DB_Fini( )
{
	if( g_DbManager != 0 )
		delete g_DbManager;
	if( g_DbManager2_ODBC != 0 )
		delete g_DbManager2_ODBC;
	if( g_DbManager2_SQLITE != 0 )
		delete g_DbManager2_SQLITE;
	g_DbDriver.clear();
}

BTNM_Export_C DbManager* ___get_DbManager( )
{
	return g_DbManager;
}

BTNM_Export_C DbManager2* ___get_DbManager2( const char* driver )
{
	if( tstrcasencmp( driver, ODBC_DRIVER) == 0 )
		return g_DbManager2_ODBC;
	else if( tstrcasencmp( driver, SQLITE_DRIVER) == 0 )
		return g_DbManager2_SQLITE;
	else
		return 0;
}

BTNM_Export_C const char* ___get_DbDriver( )
{
	return g_DbDriver.c_str();
}

_jomoo_db_end