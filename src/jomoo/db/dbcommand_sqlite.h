#ifndef _DbCommand_SQLITE_h_
#define _DbCommand_SQLITE_h_

# include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_db.h"
# include <list>
# include "DbConnection_SQLITE.h"
# include "spi/command.h"
# include "sqlite_wrapper.h"

_jomoo_db_begin

namespace spi
{

class DbCommand_SQLITE : public command
{
public:
	DbCommand_SQLITE( DbConnection_SQLITE* con );
	~DbCommand_SQLITE();
	
	bool direct_exec( const tchar* sql, size_t len , bool reportWarningsAsErrors );
	bool prepare( const tchar* sql, size_t len, bool reportWarningsAsErrors = true );
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
	bool bind( int index, const Timespan& time );

	bool bind( const tchar* columnName, bool value );
	bool bind( const tchar* columnName, int8_t value );
	bool bind( const tchar* columnName, int16_t value );
	bool bind( const tchar* columnName, int32_t value );
	bool bind( const tchar* columnName, int64_t value );
	bool bind( const tchar* columnName, double value );
	bool bind( const tchar* columnName, const char* str , size_t n);
	bool bind( const tchar* columnName, const Timestamp& time );
	bool bind( const tchar* columnName, const Timespan& time_span );

	DECLARE_SHARED( );
private:

	DbConnection_SQLITE *con_;

	const tchar* tail_;
	//
	sqlite3_stmt   *stmt_;

	std::list< tstring > buffer_;
};

}

_jomoo_db_end

#endif // _DbCommand_SQLITE_h_