
#include "stdafx.h"
#include <windows.h>
#include "DbConnection_ODBC.h"
#include "DbQuery_ODBC.h"
#include "DbExecute_ODBC.h"

_bt_begin

DbConnection_ODBC::DbConnection_ODBC(const tstring& name) : name_(name)
{
	if( !open( name ) )
		throw std::runtime_error( error_ );
		
}

DbConnection_ODBC::~DbConnection_ODBC()
{
	close();
}

const tstring& DbConnection_ODBC::name() const
{
	return name_;
}

bool DbConnection_ODBC::open(const tstring& parameters)
{
	SQLRETURN r;

	// Allocate an environment handle
	r = SQLAllocHandle(
		SQL_HANDLE_ENV,          // HandleType
		SQL_NULL_HANDLE,         // InputHandle
		&dbe_);                  // OutputHandlePtr
	if (SQLERROR(r)) 
	{
		error_ = "分配环境句柄失败";
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
		error_ = "设置环境句柄属性失败";
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
		error_ = "分配数据库句柄失败";
		SQLFreeHandle(SQL_HANDLE_ENV, dbe_);
		return false;
	}

	// Opens the connection
	SQLCHAR    *odbcDSN = (SQLCHAR*)parameters.c_str();
	SQLSMALLINT odbcDSBSize = (SQLSMALLINT)parameters.size();
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
		reportError_("不能打开数据库", SQL_HANDLE_DBC, dbc_);
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

bool DbConnection_ODBC::uses(const tstring& database)
{
	SQLCHAR    *odbcBase     = (SQLCHAR*)database.c_str();
	SQLSMALLINT odbcBaseSize = (SQLSMALLINT)database.size();

	SQLSetConnectAttr(
		dbc_,                       // ConnectionHandle
		SQL_ATTR_CURRENT_CATALOG,   // Attribute
		odbcBase,                   // ValuePtr
		odbcBaseSize);              // StringLength
	return true;
}

void DbConnection_ODBC::reportError_(const tstring& message, SQLSMALLINT handleType, SQLHANDLE handle)
{
	tstring odbcDetails = "??";
	tstring odbcState   = "??";
	{
		SQLCHAR state[15];
		SQLINTEGER code;
		SQLCHAR buffer[656];
		SQLSMALLINT tmp;

		SQLGetDiagRec(
			handleType,           // HandleType
			handle,               // Handle
			1,                    // RecNumber
			state,                // Sqlstate
			&code,                // NativeErrorPtr
			buffer,               // MessageText
			655,                  // BufferLength
			&tmp);                // TextLengthPtr
		odbcDetails = (const char*)buffer;
		odbcState   = (const char*)state;
	}
	error_ =  message;
	error_ += " (";
	error_ += odbcState ;
	error_ += ", "; 
	error_ += odbcDetails;
	error_ += ")";
}

PDbQuery DbConnection_ODBC::query()
{
	PDbQuery result(new DbQuery_ODBC(this));
	return result;
}

PDbExecute DbConnection_ODBC::execute()
{
	PDbExecute result(new DbExecute_ODBC(this));
	return result;
}

PDbQuery2 DbConnection_ODBC::query2()
{
	PDbQuery2 result(new DbQuery_ODBC(this));
	return result;
}

PDbExecute2 DbConnection_ODBC::execute2()
{
	PDbExecute2 result(new DbExecute_ODBC(this));
	return result;
}

bool DbConnection_ODBC::begin()
{
	autoCommit_(false);
	return true;
}

bool DbConnection_ODBC::commit()
{
	SQLRETURN r = SQLEndTran(
		SQL_HANDLE_DBC,     // HandleType
		dbc_,               // Handle
		SQL_COMMIT);        // CompletionType

	if (SQLERROR(r))
	{
		reportError_("不能提交一个事务", SQL_HANDLE_DBC, dbc_);
		return false;
	}

	autoCommit_(true);
	return true;
}

bool DbConnection_ODBC::rollback()
{
	SQLRETURN r = SQLEndTran(
		SQL_HANDLE_DBC,     // HandleType
		dbc_,               // Handle
		SQL_ROLLBACK);      // CompletionType

	if (SQLERROR(r))
	{
		reportError_("不能回滚一个事务", SQL_HANDLE_DBC, dbc_);
		return false;
	}

	autoCommit_(true);
	return true;
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
		reportError_("不能设置自动提交事务", SQL_HANDLE_DBC, dbc_);
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

_bt_end
