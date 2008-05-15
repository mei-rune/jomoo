
#include <windows.h>
#include "DbTransaction_SQLITE.h"


#include "include/config.h"
#ifdef _MEMORY_DEBUG 
	#undef THIS_FILE
	#define new	   DEBUG_NEW  
	#define malloc DEBUG_MALLOC  
    static char THIS_FILE[] = __FILE__;  
#endif



_jomoo_db_begin

namespace spi
{


DbTransaction_SQLITE::DbTransaction_SQLITE(DbConnection_SQLITE* conn, IsolationLevel level)
: _conn( conn )
, _level( level )
{
	if( null_ptr == _conn )
		ThrowException( NullException );

	_conn->incRef();
	if(!beginTransaction(level))
		ThrowException1( DbException, _conn->last_error() );
}

DbTransaction_SQLITE::~DbTransaction_SQLITE()
{
	release();
}

void DbTransaction_SQLITE::release()
{
	if( null_ptr == _conn )
		return;

	_conn->decRef();
	_conn = null_ptr;
}

bool DbTransaction_SQLITE::beginTransaction( IsolationLevel level )
{
	_level = level;
	char *errmsg;
	if ( tsqlite3_exec(db_, _T("BEGIN TRANSACTION"), NULL, NULL, &errmsg) != SQLITE_OK)
	{
		_conn->last_error( errmsg );
		return false;
	}
	return true;
}

bool DbTransaction_SQLITE::commit()
{
	char *errmsg;
	int result = tsqlite3_exec(db_, _T("COMMIT TRANSACTION"), NULL, NULL, &errmsg);
	if (result != SQLITE_OK)
	{
		_conn->last_error( errmsg );
		return false;
	}
	return true;
}

bool DbTransaction_SQLITE::rollback()
{
	char *errmsg;
	int result = tsqlite3_exec(db_, _T("ROLLBACK TRANSACTION"), NULL, NULL, &errmsg);
	if (result != SQLITE_OK)
	{
		_conn->last_error( errmsg );
		return false;
	}
	return true;
}

}

_jomoo_db_end
