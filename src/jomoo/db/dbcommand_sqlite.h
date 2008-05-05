#ifndef _DbExecute_SQLITE_h_
#define _DbExecute_SQLITE_h_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_db.h"
#include "../../util/Variant.h"
#ifdef _BOOST_TIME_
#include "../../util/pTime.h"
#endif
#include <list>
#include "DbExecute.h"
#include "QSqlite.h"

_jomoo_db_begin

class DbConnection_SQLITE;

class DbExecute_SQLITE : public DbExecute
{
public:
	DbExecute_SQLITE( DbConnection_SQLITE* con );
	~DbExecute_SQLITE();
	
	bool direct_exec( const tchar* sql, size_t len , bool reportWarningsAsErrors );
	bool direct_exec( const tstring& sql, bool reportWarningsAsErrors );

	bool prepare( const tchar* sql, size_t len, bool reportWarningsAsErrors = true );
	bool prepare( const tstring& sql, bool reportWarningsAsErrors = true );
	bool exec( );
	bool reset( );
	int affected_rows( );

	bool bind( int index, int value );
	bool bind( int index, __int64 value );
	bool bind( int index, double value );
	bool bind( int index, const char* str , size_t n);
	bool bind( int index, const wchar_t* str , size_t n );
	bool bind( int index, const Timestamp& time );

	bool bind( const tstring& name, int value );
	bool bind( const tstring& name, __int64 value );
	bool bind( const tstring& name, double value );
	bool bind( const tstring& name, const char* str , size_t n );
	bool bind( const tstring& name, const wchar_t* str , size_t n );
	bool bind( const tstring& name, const Timestamp& time );

	bool bind( const tchar* name, size_t len, int value );
	bool bind( const tchar* name, size_t len, __int64 value );
	bool bind( const tchar* name, size_t len, double value );
	bool bind( const tchar* name, size_t len, const char* str , size_t n );
	bool bind( const tchar* name, size_t len, const wchar_t* str , size_t n );
	bool bind( const tchar* name, size_t len, const Timestamp& time );
	
	DECLARE_SHARED( );
private:

	DbConnection_SQLITE *con_;

	const tchar* tail_;
	//
	sqlite3_stmt   *stmt_;

	std::list< tstring > buffer_;
};


_jomoo_db_end

#endif // _DbExecute_SQLITE_h_