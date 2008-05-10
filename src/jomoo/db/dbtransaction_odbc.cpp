
#include <windows.h>
#include "DbConnection_ODBC.h"
#include "DbQuery_ODBC.h"
#include "DbExecute_ODBC.h"


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


DbTransaction_ODBC::DbTransaction_ODBC(DbConnection_ODBC* odbc, IsolationLevel level)
: _odbc( odbc )
, _level( level )
{
	if( null_ptr == odbc )
		ThrowException( NullException );

	_odbc->incRef();
	_odbc->autoCommit_(true);
}

DbTransaction_ODBC::~DbTransaction_ODBC()
{
	release();
}

void DbTransaction_ODBC::release()
{
	if( null_ptr == _odbc )return;
	_odbc->decRef();
	_odbc = null_ptr;
}

bool DbTransaction_ODBC::beginTransaction( IsolationLevel level )
{
	_level = level;
	return _odbc->autoCommit_( false );
}

bool DbTransaction_ODBC::commit()
{
	SQLRETURN r = SQLEndTran(
		SQL_HANDLE_DBC,     // HandleType
		_odbc->dbc_,               // Handle
		SQL_COMMIT);        // CompletionType

	if (SQLERROR(r))
	{
		_odbc->reportError_(_T("不能提交一个事务"), SQL_HANDLE_DBC, dbc_);
		return false;
	}

	_odbc->autoCommit_(true);
	return true;
}

bool DbTransaction_ODBC::rollback()
{
	SQLRETURN r = SQLEndTran(
		SQL_HANDLE_DBC,     // HandleType
		_odbc->dbc_,               // Handle
		SQL_ROLLBACK);      // CompletionType

	if (SQLERROR(r))
	{
		_odbc->reportError_( _T("不能回滚一个事务"), SQL_HANDLE_DBC, dbc_);
		return false;
	}

	_odbc->autoCommit_(true);
	return true;
}

}

_jomoo_db_end
