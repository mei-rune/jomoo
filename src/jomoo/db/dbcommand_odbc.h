#ifndef _DbExecute_ODBC_h_
#define _DbExecute_ODBC_h_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_db.h"
# include "spi/command.h"
# include "DbConnection_ODBC.h"
# include <sql.h>

_jomoo_db_begin

namespace spi
{

class DbCommand_ODBC : public command
{
public:
	DbCommand_ODBC( DbConnection_ODBC* odbc , int timeout = 120 );
	~DbCommand_ODBC();

	bool direct_exec( const tchar* sql, size_t len , bool reportWarningsAsErrors );
	bool prepare( const tchar* sql, size_t len, bool reportWarningsAsErrors = true );
	bool prepare( const tstring& sql, bool reportWarningsAsErrors = true );
	bool exec( );
	bool reset( );
	int affected_rows( );

	bool bind( int index, bool value );
	bool bind( int index, int8_t value );
	bool bind( int index, int16_t value );
	bool bind( int index, int32_t value );
	bool bind( int index, int64_t value );
	bool bind( int index, double value );
	bool bind( int index, const char* str , size_t n);
	bool bind( int index, const Timestamp& time );


	bool bind( const tchar* columnName, bool value );
	bool bind( const tchar* columnName, int8_t value );
	bool bind( const tchar* columnName, int16_t value );
	bool bind( const tchar* columnName, int32_t value );
	bool bind( const tchar* columnName, int64_t value );
	bool bind( const tchar* columnName, double value );
	bool bind( const tchar* columnName, const char* str , size_t n);
	bool bind( const tchar* columnName, const Timestamp& time );

	DECLARE_SHARED( );
private:
	
	void reportError_( const tstring& message );

	DbConnection_ODBC *con_;
	//
	SQLHSTMT   stmt_;

	SQLCHAR    *sqlText_;
	SQLSMALLINT sqlTextSize_;

	// error handling
	bool reportWarningsAsErrors_;
};

}

_jomoo_db_end

#endif // _DbExecute_ODBC_h_