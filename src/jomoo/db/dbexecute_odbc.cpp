
#include <windows.h>
#include "DbExecute_ODBC.h"
#include "DbConnection_ODBC.h"

#include "include/config.h"
#ifdef _MEMORY_DEBUG 
	#undef THIS_FILE
	#define new	   DEBUG_NEW  
	#define malloc DEBUG_MALLOC  
    static char THIS_FILE[] = __FILE__;  
#endif




_jomoo_db_begin

DbExecute_ODBC::DbExecute_ODBC( DbConnection_ODBC* con , int timeout )
: con_(con)
, stmt_(NULL)
, sqlText_( NULL )
, sqlTextSize_( 0 )
{
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

DbExecute_ODBC::~DbExecute_ODBC()
{

	SQLFreeHandle(SQL_HANDLE_STMT, stmt_);
	
}

bool DbExecute_ODBC::prepare( const tchar* sql, size_t len, bool reportWarningsAsErrors )
{
	reportWarningsAsErrors_ = reportWarningsAsErrors;
	sqlText_ = (SQLCHAR*)sql;
	sqlTextSize_ = (SQLSMALLINT)len;
	return true;
}

bool DbExecute_ODBC::prepare(const tstring& sql, bool reportWarningsAsErrors ) 
{
	return prepare( sql.c_str(), sql.size() );
}

bool DbExecute_ODBC::reset( ) 
{
	return true;
}

bool DbExecute_ODBC::exec( )
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

bool DbExecute_ODBC::bind( int index, int value )
{
	SQLRETURN retcode = SQLBindParameter( stmt_, index, SQL_PARAM_INPUT, SQL_C_SLONG,SQL_INTEGER, 0, 0, &value, 0, 0 );
	if ( (retcode == SQL_SUCCESS) || (retcode == SQL_SUCCESS_WITH_INFO) )
		return true;
	reportError_( _T("在绑定[") + convertIntegerToString( index ) + _T("]时") );
	return false;
}

bool DbExecute_ODBC::bind( int index, __int64 value )
{ //sqlite3_bind_int64
	SQLRETURN retcode = SQLBindParameter( stmt_, index, SQL_PARAM_INPUT, SQL_C_SBIGINT,SQL_BIGINT, 0, 0, &value, 0, 0 );
	if ( (retcode == SQL_SUCCESS) || (retcode == SQL_SUCCESS_WITH_INFO) )
		return true;
	reportError_( _T("在绑定[") + convertIntegerToString( index ) + ("]时") );
	return false;
}

bool DbExecute_ODBC::bind( int index, double value )
{ // sqlite3_bind_double
	SQLRETURN retcode = SQLBindParameter( stmt_, index, SQL_PARAM_INPUT, SQL_C_DOUBLE,SQL_DOUBLE, 0, 0, &value, 0, 0 );
	if ( (retcode == SQL_SUCCESS) || (retcode == SQL_SUCCESS_WITH_INFO) )
		return true;
	reportError_( "在绑定[" + convertIntegerToString( index ) + "]时" );
	return false;
}

bool DbExecute_ODBC::bind( int index, const char* str, size_t n )
{// sqlite3_bind_text
SQLINTEGER len = ( SQLINTEGER ) n;
	SQLRETURN retcode = SQLBindParameter( stmt_, index, SQL_PARAM_INPUT, SQL_C_CHAR,SQL_CHAR, len, 0, &str, 0, &len );
	if ( (retcode == SQL_SUCCESS) || (retcode == SQL_SUCCESS_WITH_INFO) )
		return true;
	reportError_( "在绑定[" + convertIntegerToString( index ) + "]时" );
	return false;
}

bool DbExecute_ODBC::bind( int index, const wchar_t* str, size_t n )
{ // sqlite3_bind_text16
	SQLINTEGER len = ( SQLINTEGER ) n;
	SQLRETURN retcode = SQLBindParameter( stmt_, index, SQL_PARAM_INPUT, SQL_C_CHAR,SQL_CHAR, 0, len, &str, 0, &len );
	if ( (retcode == SQL_SUCCESS) || (retcode == SQL_SUCCESS_WITH_INFO) )
		return true;
	reportError_( "在绑定[" + convertIntegerToString( index ) + "]时" );
	return false;
}

bool DbExecute_ODBC::bind( int index, const Timestamp& time )
{
	pdate date= time.date();
	ptime_duration time_duration = time.time_of_day();
	SQLRETURN retcode;

	if(  !date.is_not_a_date() )
	{
	SQL_TIMESTAMP_STRUCT timestamp;
	timestamp.year =( SQLSMALLINT ) date.year();
    timestamp.month = ( SQLUSMALLINT ) date.month();
    timestamp.day = ( SQLUSMALLINT ) date.day();
    timestamp.hour = ( SQLUSMALLINT ) time_duration.hours();
    timestamp.minute = ( SQLUSMALLINT ) time_duration.minutes();
    timestamp.second = ( SQLUSMALLINT ) time_duration.seconds();
    timestamp.fraction = ( SQLUINTEGER ) 0;
	SQLINTEGER len = sizeof( timestamp );
	retcode = SQLBindParameter( stmt_, index, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP,SQL_TIMESTAMP, 0, 0, &timestamp, 0, &len );
	}
	else
	{
	TIME_STRUCT time;
    time.hour = ( SQLUSMALLINT ) time_duration.hours();
    time.minute = ( SQLUSMALLINT ) time_duration.minutes();
    time.second = ( SQLUSMALLINT ) time_duration.seconds();
	SQLINTEGER len = sizeof( time );
		retcode = SQLBindParameter( stmt_, index, SQL_PARAM_INPUT, SQL_C_TYPE_TIME,SQL_TIME, 0, 0, &time, 0, &len );
	}
	if ( (retcode == SQL_SUCCESS) || (retcode == SQL_SUCCESS_WITH_INFO) )
		return true;
	reportError_( _T("在绑定[") + convertIntegerToString( index ) + _T("]时") );
	return false;
}

bool DbExecute_ODBC::bind( const tchar* name, size_t len, int value )
{
	//int index = sqlite3_bind_parameter_index( stmt_, name.c_str() );
	//if( index == 0 )
	//{
		con_->last_error( _T("指定的列名[") + tstring( name ) + _T("]不存在!") );
		return false;
	//}

	//return bind( index, value );
}

bool DbExecute_ODBC::bind( const tstring& name,int value )
{
	return bind( name.c_str(), name.size(), value );
}

bool DbExecute_ODBC::bind( const tchar* name, size_t len, __int64 value )
{
	//int index = sqlite3_bind_parameter_index( stmt_, name.c_str() );
	//if( index == 0 )
	//{
		con_->last_error( _T("指定的列名[") + tstring( name ) + _T("]不存在!") );
		return false;
	//}

	//return bind( index, value );
}

bool DbExecute_ODBC::bind( const tstring& name,__int64 value )
{
	return bind( name.c_str(), name.size(), value );
}

bool DbExecute_ODBC::bind( const tchar* name, size_t len, double value )
{
	//int index = sqlite3_bind_parameter_index( stmt_, name.c_str() );
	//if( index == 0 )
	//{
		con_->last_error( _T("指定的列名[") + tstring( name ) + _T("]不存在!") );
		return false;
	//}

	//return bind( index, value );
}

bool DbExecute_ODBC::bind( const tstring& name,double value )
{
	return bind( name.c_str(), name.size(), value );
}

bool DbExecute_ODBC::bind( const tchar* name, size_t len, const char* str , size_t n )
{
	//int index = sqlite3_bind_parameter_index( stmt_, name.c_str() );
	//if( index == 0 )
	//{
		con_->last_error( _T("指定的列名[") + tstring( name ) + _T("]不存在!") );
		return false;
	//}

	//return bind( index, str ,n );
}

bool DbExecute_ODBC::bind( const tstring& name,const char* str , size_t n )
{
	return bind( name.c_str(), name.size(), str,n );
}

bool DbExecute_ODBC::bind( const tchar* name, size_t len, const wchar_t* str , size_t n )
{
	//int index = sqlite3_bind_parameter_index( stmt_, name.c_str() );
	//if( index == 0 )
	//{
		con_->last_error( _T("指定的列名[") + tstring( name ) + _T("]不存在!") );
		return false;
	//}

	//return bind( index, str ,n );
}

bool DbExecute_ODBC::bind( const tstring& name,const wchar_t* str , size_t n )
{
	return bind( name.c_str(), name.size(), str,n );
}

bool DbExecute_ODBC::bind( const tchar* name, size_t len, const ptime& time )
{
	//int index = sqlite3_bind_parameter_index( stmt_, name.c_str() );
	//if( index == 0 )
	//{
		con_->last_error( _T("指定的列名[") + tstring( name ) + _T("]不存在!") );
		return false;
	//}

	//return bind( index, time );
}

bool DbExecute_ODBC::bind( const tstring& name, const ptime& time )
{
	return bind( name.c_str(), name.size(), time );
}

void DbExecute_ODBC::reportError_(const tstring& message)
{
	con_->reportError_(message, SQL_HANDLE_STMT, stmt_);
}

int DbExecute_ODBC::affected_rows( )
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

bool DbExecute_ODBC::direct_exec( const tchar* sql, size_t len , bool reportWarningsAsErrors )
{
	if( ! prepare( sql, len, reportWarningsAsErrors ) )
		return false;
	return exec();
}

bool DbExecute_ODBC::direct_exec( const tstring& sql, bool reportWarningsAsErrors )
{
	if( ! prepare( sql, reportWarningsAsErrors ) )
		return false;
	return exec();
}

DEFINE_SHARED( DbExecute_ODBC );

_jomoo_db_end

