
#include "DbConnection_SQLITE.h"
#include "DbQuery_SQLITE.h"
#include "DbCommand_SQLITE.h"
#include "DbTransaction_SQLITE.h"
#include "sqlite_function.h"

#ifdef _MEMORY_DEBUG 
	#undef THIS_FILE
	#define new	   DEBUG_NEW  
	#define malloc DEBUG_MALLOC  
    static char THIS_FILE[] = __FILE__;  
#endif

_jomoo_db_begin

namespace spi
{

DbConnection_SQLITE::DbConnection_SQLITE(const tstring& name) : name_(name)
, db_( 0 )
{
	if (tsqlite3_open(name.c_str(), &db_) != SQLITE_OK || db_ == NULL)		
		ThrowException1( DbException, _T("打开数据库[") + name + _T("]失败") );

	for( int i=0; i< g_sqlite_fun_count; i++ )
	{
		if( tsqlite3_create_function( db_
			, g_sqlite_fun[i].zFunctionName
			, g_sqlite_fun[i].nArg
			, g_sqlite_fun[i].eTextRep
			, g_sqlite_fun[i].pUserData
			, g_sqlite_fun[i].xFunc
			, g_sqlite_fun[i].xStep
			, g_sqlite_fun[i].xFinal ) != SQLITE_OK )
			ThrowException1( DbException, _T("DbConnection_SQLITE > 注册函数") + toTstring( g_sqlite_fun[i].zFunctionName )+ _T("时失败") );
	}
}

DbConnection_SQLITE::~DbConnection_SQLITE()
{
	close();
}

const tstring& DbConnection_SQLITE::name() const
{
	return name_;
}

bool DbConnection_SQLITE::open(const tchar* parameters, size_t len)
{
	if ( db_ != NULL )
		tsqlite3_close(db_);

	if (tsqlite3_open(parameters, &db_) != SQLITE_OK || db_ == NULL)
	{
		last_error( db_ );
		return false;
	}

	
	if( -1 == len )
		name_ = parameters;
	else
		name_.assign( parameters, len);

	return true;
}

void DbConnection_SQLITE::close()
{
	if ( db_ != NULL )
		tsqlite3_close(db_);
	db_ = NULL;
}

bool DbConnection_SQLITE::uses(const tchar* database, size_t len)
{
	// NOP]
	last_error( _T("不支持的操作") );
	return false;
}

query* DbConnection_SQLITE::createQuery()
{
	return new DbQuery_SQLITE(this);
}

command* DbConnection_SQLITE::createCommand()
{
	return new DbCommand_SQLITE( this );
}

transaction* DbConnection_SQLITE::beginTransaction( IsolationLevel level )
{
	return new DbTransaction_SQLITE( this, level );
}

const tstring& DbConnection_SQLITE::last_error(char *message)
{
	if (message != NULL)
	{
		error_ = message;
		tsqlite3_free(message);
	}
	return error_;
}

const tstring& DbConnection_SQLITE::last_error( const tstring& message)
{
	error_ = message;
	return error_;
}

const tstring& DbConnection_SQLITE::last_error( ) const
{
	return error_;
}

const tstring& DbConnection_SQLITE::last_error( sqlite3* message )
{
	if (message != NULL)
	{
		const char* err = tsqlite3_errmsg( message );
		if( err != 0 )
			error_ = toTstring(err);
	}
	return error_;
}

DEFINE_SHARED( DbConnection_SQLITE )

}

_jomoo_db_end
