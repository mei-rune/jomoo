
#include <windows.h>
#include "DbCommand_ODBC.h"
#include "DbConnection_ODBC.h"
#include "DbTransaction_ODBC.h"

#include "include/config.h"
#ifdef _MEMORY_DEBUG 
	#undef THIS_FILE
	#define new	   DEBUG_NEW  
	#define malloc DEBUG_MALLOC  
    static char THIS_FILE[] = __FILE__;  
#endif

_jomoo_db_begin

DbCommand_ODBC::DbCommand_ODBC( DbConnection_ODBC* odbc , int timeout )
: con_( odbc )
, stmt_(NULL)
, sqlText_( NULL )
, sqlTextSize_( 0 )
{
	if( null_ptr == odbc )
		ThrowException( NullException );

	con_->incRef();

		// Allocate a statement handle
	SQLRETURN r = SQLAllocHandle(
		SQL_HANDLE_STMT,             // HandleType
		con_->dbc_,                  // InputHandle
		&stmt_);                      // OutputHandlePtr
	if (SQLERROR(r))
	{
		ThrowException1( DbException, _T("取得odbc执行句柄失败") );
	}

	// Make sure we are in Forward Only cursor
	r = SQLSetStmtAttr(
		stmt_,                                 // StatementHandle
		SQL_ATTR_CURSOR_TYPE,                 // Attribute
		(SQLPOINTER)SQL_CURSOR_FORWARD_ONLY,  // ValuePtr
		SQL_IS_UINTEGER);                     // StringLength
	if (SQLERROR(r))
	{
		SQLFreeHandle(SQL_HANDLE_STMT, stmt_);
		ThrowException1( DbException, _T("设置odbc执行句柄光标属性失败") );
	}
	//// Make sure we are in synchronous mode
	//r = SQLSetStmtAttr(
	//	stmt_,                                 // StatementHandle
	//	SQL_ATTR_ASYNC_ENABLE,                // Attribute
	//	(SQLPOINTER)SQL_ASYNC_ENABLE_OFF,     // ValuePtr
	//	SQL_IS_UINTEGER);                     // StringLength
	//if (SQLERROR(r))
	//{
	//	SQLFreeHandle(SQL_HANDLE_STMT, stmt_);
	//	ThrowException1( DbException, _T("设置odbc执行句柄异步属性失败") );
	//}
	//// Change the time out
	//SQLUINTEGER sqlTimeout = timeout;
	//r = SQLSetStmtAttr(
	//	stmt_,                                 // StatementHandle
	//	SQL_ATTR_QUERY_TIMEOUT,               // Attribute
	//	(SQLPOINTER)sqlTimeout,               // ValuePtr
	//	SQL_IS_UINTEGER);                     // StringLength
	//if (SQLERROR(r))
	//{
	//	SQLFreeHandle(SQL_HANDLE_STMT, stmt_);
	//	ThrowException1( DbException, _T("设置odbc执行句柄超时属性失败") );
	//}
}

DbCommand_ODBC::~DbCommand_ODBC()
{
	SQLFreeHandle(SQL_HANDLE_STMT, stmt_);
	release();
}

void DbExecute_ODBC::release()
{
	if( null_ptr == con_ )return;
	con_->decRef();
	con_ = null_ptr;
}

bool DbCommand_ODBC::prepare( const tchar* sql, size_t len, bool reportWarningsAsErrors )
{
	reportWarningsAsErrors_ = reportWarningsAsErrors;
	sqlText_ = (SQLCHAR*)sql;
	if( -1 == len)
		len = string_traits< tchar>::strlen( sql );

	sqlTextSize_ = (SQLSMALLINT)len;
	return true;
}

bool DbCommand_ODBC::reset( ) 
{
	return true;
}

bool DbCommand_ODBC::exec( )
{	
	SQLRETURN r = SQLExecDirect(
		stmt_,                        // StatementHandle
		sqlText_,                     // StatementText
		sqlTextSize_);                // TextLength

	switch(r) {
	case SQL_SUCCESS:
	case SQL_NO_DATA:
		return true;

	case SQL_SUCCESS_WITH_INFO:
		if (reportWarningsAsErrors_)
		{
			reportError_(_T("在执行语句 '")+ toTstring( ( const char* )sqlText_) + _T("'时"));
		}
		else
		{
			return true;
		}
		break;

	default:
		reportError_(_T("在执行语句 '")+ toTstring( ( const char* )sqlText_) +_T("'时"));
	}
	return false;
}

bool DbCommand_ODBC::bind( int index, bool value )
{
	return bind( index, (int)(value?1:0));
}

bool DbCommand_ODBC::bind( int index, int8_t value )
{
	SQLRETURN retcode = SQLBindParameter( stmt_, index, SQL_PARAM_INPUT, SQL_C_STINYINT,SQL_TINYINT, 0, 0, &value, 0, 0 );
	if ( (retcode == SQL_SUCCESS) || (retcode == SQL_SUCCESS_WITH_INFO) )
		return true;
	reportError_( _T("在绑定[") + convertIntegerToString( index ) + _T("]时") );
	return false;
}

bool DbCommand_ODBC::bind( int index, int16_t value )
{
	SQLRETURN retcode = SQLBindParameter( stmt_, index, SQL_PARAM_INPUT, SQL_C_SSHORT,SQL_SMALLINT, 0, 0, &value, 0, 0 );
	if ( (retcode == SQL_SUCCESS) || (retcode == SQL_SUCCESS_WITH_INFO) )
		return true;
	reportError_( _T("在绑定[") + convertIntegerToString( index ) + _T("]时") );
	return false;
}

bool DbCommand_ODBC::bind( int index, int32_t value )
{
	SQLRETURN retcode = SQLBindParameter( stmt_, index, SQL_PARAM_INPUT, SQL_C_SLONG,SQL_INTEGER, 0, 0, &value, 0, 0 );
	if ( (retcode == SQL_SUCCESS) || (retcode == SQL_SUCCESS_WITH_INFO) )
		return true;
	reportError_( _T("在绑定[") + convertIntegerToString( index ) + _T("]时") );
	return false;
}

bool DbCommand_ODBC::bind( int index, int64_t value )
{
	SQLRETURN retcode = SQLBindParameter( stmt_, index, SQL_PARAM_INPUT, SQL_C_SBIGINT,SQL_BIGINT, 0, 0, &value, 0, 0 );
	if ( (retcode == SQL_SUCCESS) || (retcode == SQL_SUCCESS_WITH_INFO) )
		return true;
	reportError_( _T("在绑定[") + convertIntegerToString( index ) + _T("]时") );
	return false;
}

bool DbCommand_ODBC::bind( int index, double value )
{ // sqlite3_bind_double
	SQLRETURN retcode = SQLBindParameter( stmt_, index, SQL_PARAM_INPUT, SQL_C_DOUBLE,SQL_DOUBLE, 0, 0, &value, 0, 0 );
	if ( (retcode == SQL_SUCCESS) || (retcode == SQL_SUCCESS_WITH_INFO) )
		return true;
	reportError_( "在绑定[" + convertIntegerToString( index ) + "]时" );
	return false;
}

bool DbCommand_ODBC::bind( int index, const char* str, size_t n )
{// sqlite3_bind_text
	SQLINTEGER len = ( SQLINTEGER ) n;
	SQLRETURN retcode = SQLBindParameter( stmt_, index, SQL_PARAM_INPUT, SQL_C_CHAR,SQL_VARCHAR, len, 0, &str, 0, &len );
	if ( (retcode == SQL_SUCCESS) || (retcode == SQL_SUCCESS_WITH_INFO) )
		return true;
	reportError_( "在绑定[" + convertIntegerToString( index ) + "]时" );
	return false;
}

bool DbCommand_ODBC::bind( int index, const Timestamp& time )
{
	DateTime date( time );
	SQL_TIMESTAMP_STRUCT timestamp;
	timestamp.year =( SQLSMALLINT ) date.year();
    timestamp.month = ( SQLUSMALLINT ) date.month();
    timestamp.day = ( SQLUSMALLINT ) date.day();
    timestamp.hour = ( SQLUSMALLINT ) date.hour();
    timestamp.minute = ( SQLUSMALLINT ) date.minute();
    timestamp.second = ( SQLUSMALLINT ) date.second();
    timestamp.fraction = ( SQLUINTEGER ) 0;
	SQLINTEGER len = sizeof( timestamp );
	retcode = SQLBindParameter( stmt_, index, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP,SQL_TIMESTAMP, 0, 0, &timestamp, 0, &len );
	if ( (retcode == SQL_SUCCESS) || (retcode == SQL_SUCCESS_WITH_INFO) )
		return true;
	reportError_( _T("在绑定[") + convertIntegerToString( index ) + _T("]时") );
	return false;
}

bool DbCommand_ODBC::bind( int index, const Timespan& time )
{
	return bind( index, time.totalMicroseconds );
}

bool DbCommand_ODBC::bind( const tchar* columnName, bool value )
{
		con_->last_error( _T("指定的列名[") + tstring( name ) + _T("]不存在!") );
		return false;
}

bool DbCommand_ODBC::bind( const tchar* columnName, int8_t value )
{
		con_->last_error( _T("指定的列名[") + tstring( name ) + _T("]不存在!") );
		return false;
}

bool DbCommand_ODBC::bind( const tchar* columnName, int16_t value )
{
		con_->last_error( _T("指定的列名[") + tstring( name ) + _T("]不存在!") );
		return false;
}

bool DbCommand_ODBC::bind( const tchar* columnName, int32_t value )
{
		con_->last_error( _T("指定的列名[") + tstring( name ) + _T("]不存在!") );
		return false;
}

bool DbCommand_ODBC::bind( const tchar* columnName, int64_t value )
{
		con_->last_error( _T("指定的列名[") + tstring( name ) + _T("]不存在!") );
		return false;
}

bool DbCommand_ODBC::bind( const tchar* columnName, double value )
{
		con_->last_error( _T("指定的列名[") + tstring( name ) + _T("]不存在!") );
		return false;
}

bool DbCommand_ODBC::bind( const tchar* columnName, const char* str , size_t n )
{
		con_->last_error( _T("指定的列名[") + tstring( name ) + _T("]不存在!") );
		return false;
}

bool DbCommand_ODBC::bind( const tchar* columnName, const Timespan& time_span )
{
		con_->last_error( _T("指定的列名[") + tstring( name ) + _T("]不存在!") );
		return false;
}

void DbCommand_ODBC::reportError_(const tstring& message)
{
	con_->reportError_(message, SQL_HANDLE_STMT, stmt_);
}

int DbCommand_ODBC::affected_rows( )
{
	SQLINTEGER     RowCount = 0; 
	SQLRETURN r = SQLRowCount( stmt_,& RowCount );
	if (SQLERROR(r))
	{
		reportError_( _T("在读改动行数据时") );
		return -1;
	}
	return RowCount;
}

bool DbCommand_ODBC::direct_exec( const tchar* sql, size_t len , bool reportWarningsAsErrors )
{
	if( ! prepare( sql, len, reportWarningsAsErrors ) )
		return false;
	return exec();
}

bool DbCommand_ODBC::direct_exec( const tstring& sql, bool reportWarningsAsErrors )
{
	if( ! prepare( sql, reportWarningsAsErrors ) )
		return false;
	return exec();
}

DEFINE_SHARED( DbCommand_ODBC );

_jomoo_db_end

