
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

DbConnection_ODBC::DbConnection_ODBC()
{
}

DbConnection_ODBC::~DbConnection_ODBC()
{
	close();
}

const tstring& DbConnection_ODBC::name() const
{
	return name_;
}

bool DbConnection_ODBC::open(const tchar* parameters, size_t len)
{
	if( -1 == len )
		name_ = parameters;
	else
		name_.assign( parameters , len );

	SQLRETURN r;

	// Allocate an environment handle
	r = SQLAllocHandle(
		SQL_HANDLE_ENV,          // HandleType
		SQL_NULL_HANDLE,         // InputHandle
		&dbe_);                  // OutputHandlePtr
	if (SQLERROR(r)) 
	{
		error_ = _T("分配环境句柄失败");
		return false;
	}

	// Declare the ODBC version we'll use
	r = SQLSetEnvAttr(
		dbe_,                      // EnvironmentHandle
		SQL_ATTR_ODBC_VERSION,     // Attribute
		(SQLPOINTER)SQL_OV_ODBC3,  // ValuePtr
		SQL_IS_UINTEGER);          // StringLength)
	if (SQLERROR(r)) 
	{
		error_ = _T("设置环境句柄属性失败");
		SQLFreeHandle(SQL_HANDLE_ENV, dbe_);
		return false;
	}

	// Allocate a db handle
	r = SQLAllocHandle(
		SQL_HANDLE_DBC,          // HandleType
		dbe_,                    // InputHandle
		&dbc_);                  // OutputHandlePtr
	if (SQLERROR(r))
	{
		error_ = _T("分配数据库句柄失败");
		SQLFreeHandle(SQL_HANDLE_ENV, dbe_);
		return false;
	}

	// Opens the connection
	SQLCHAR    *odbcDSN = (SQLCHAR*)name_.c_str();
	SQLSMALLINT odbcDSBSize = (SQLSMALLINT)name_.size();
	SQLCHAR     dummy[256];
	SQLSMALLINT dummySize;

	r = SQLDriverConnect(
		dbc_,                    // ConnectionHandle
		0,                       // WindowHandle
		odbcDSN,                 // InConnectionString
		odbcDSBSize,             // StringLength1
		dummy,                   // OutConnectionString
		255,                     // BufferLength
		&dummySize,              // StringLength2Ptr
		SQL_DRIVER_COMPLETE);    // DriverCompletion

	if (SQLERROR(r))
	{
		reportError_(_T("不能打开数据库[") + name_ + _T("]"), SQL_HANDLE_DBC, dbc_);
		return false;
	}

	autoCommit_(true);
	return true;
}

void DbConnection_ODBC::close()
{
	SQLDisconnect(dbc_);

	SQLFreeHandle(SQL_HANDLE_DBC, dbc_);
	SQLFreeHandle(SQL_HANDLE_ENV, dbe_);
}

bool DbConnection_ODBC::uses(const tchar* database, size_t len)
{
	SQLCHAR    *odbcBase     = (SQLCHAR*)database.c_str();
	if( -1 == len )
		len = string_traits< tchar >::strlen( database );
	SQLSMALLINT odbcBaseSize = (SQLSMALLINT)len;

	SQLSetConnectAttr(
		dbc_,                       // ConnectionHandle
		SQL_ATTR_CURRENT_CATALOG,   // Attribute
		odbcBase,                   // ValuePtr
		odbcBaseSize);              // StringLength
	return true;
}

void DbConnection_ODBC::reportError_(const tstring& message, SQLSMALLINT handleType, SQLHANDLE handle)
{
	error_ =  message;
	bool first = true;
	{
		SQLCHAR state[  SQL_MAX_MESSAGE_LENGTH + 1  ];
		SQLINTEGER code;
		SQLCHAR buffer[ SQL_MAX_MESSAGE_LENGTH + 1 ];
		SQLSMALLINT tmp;

		while ( SQL_NO_DATA != SQLGetDiagRec(
			handleType,           // HandleType
			handle,               // Handle
			1,                    // RecNumber
			state,                // Sqlstate
			&code,                // NativeErrorPtr
			buffer,               // MessageText
			SQL_MAX_MESSAGE_LENGTH,                  // BufferLength
			&tmp) )               // TextLengthPtr
			{
				if( first )
				{
					first = false;
					error_ += _T(" {");
				}
				buffer[ SQL_MAX_MESSAGE_LENGTH ] = 0;
				error_ +=  toTstring( (const char*)state );
				error_ += _T(",");
				error_ += toTstring( (const char*)buffer);
				error_ += _T("\r\n");
			}
			if( !first )
				error_ += _T("}");
	}
}

query* DbConnection_ODBC::createQuery()
{
	return new DbQuery_ODBC(this);
}

command* DbConnection_ODBC::createCommand()
{
	return new DbExecute_ODBC(this);
}

transaction* DbConnection_ODBC::beginTransaction( IsolationLevel level)
{
	return new DbTransaction_ODBC( this, level );
}

bool DbConnection_ODBC::autoCommit_(bool on)
{

	SQLUINTEGER value;
	if (on)
		value = SQL_AUTOCOMMIT_ON;
	else
		value = SQL_AUTOCOMMIT_OFF;

	SQLRETURN r = SQLSetConnectAttr(
		dbc_,                 // ConnectionHandle
		SQL_ATTR_AUTOCOMMIT,  // Attribute
		(SQLPOINTER) value,   // ValuePtr
		SQL_IS_UINTEGER);     // StringLength

	if (SQLERROR(r))
	{
		reportError_(_T("不能设置自动提交事务"), SQL_HANDLE_DBC, dbc_);
		return false;
	}
	return true;
}

const tstring& DbConnection_ODBC::last_error( ) const
{
	return error_;
}

const tstring& DbConnection_ODBC::last_error( const tstring& message )
{
	error_ = message;
	return error_;
}

DEFINE_SHARED( DbConnection_ODBC );

}

_jomoo_db_end
