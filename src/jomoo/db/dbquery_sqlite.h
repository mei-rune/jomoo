
#ifndef _DbQuery_SQLITE_H_
#define _DbQuery_SQLITE_H_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_db.h"
#define HAVE_DB_SQLITE

#include <vector>
#include "sqlite/sqlite3.h"
#include "QSqlite.h"
#include "DbQuery.h"

_jomoo_db_begin

class DbConnection_SQLITE;

class DbQuery_SQLITE : public DbQuery2
{
public:
	DbQuery_SQLITE(DbConnection_SQLITE* con, int timeout = 120);
	virtual ~DbQuery_SQLITE();

	virtual bool exec(const char* sql, size_t len, bool reportWarningsAsErrors = true );
	virtual bool exec(const tstring& sql, bool reportWarningsAsErrors = true);
	virtual bool nextRow();
	virtual bool nextSet();
	virtual int  columns();

	virtual const Variant&     get(u_int_t column);
	virtual const Variant&     get(const tstring& column);

	bool getBoolean(u_int_t column);
	bool getBoolean(const tstring& column);
	int getInt(u_int column);
	int getInt(const tstring& column);
	__int64 getInt64(u_int column);
	__int64 getInt64(const tstring& column);
	double getDouble(u_int column);
	double getDouble(const tstring& column);
	const tstring& getString(u_int column);
	const tstring& getString(const tstring& column);

#ifdef _BOOST_TIME_
	const ptime& getTime(u_int column);
	const ptime& getTime(const tstring& column);
#endif

	int getColumnType( size_t pos );
	const tstring& getColumnName( size_t pos );

private:
	DbConnection_SQLITE *con_;

	const tchar* tail_;
	tstring sql_str_;

	//
	sqlite3_stmt   *stmt_;
	// row data
	Variant            result_;
	tstring		String_;

#ifdef _BOOST_TIME_
	ptime		Time_;
#endif

	bool         firstRow_;

	bool               columnTypesReady_;

	// columns type description
	typedef std::vector<Variant_Type::Type> ColumnTypes;
	ColumnTypes        columnTypes_;
	// columns names
	typedef std::vector<tstring> ColumnNames;
	ColumnNames        columnNames_;

	int columns_;

	bool nextSet_();

	bool fetchRow_();
	bool fetchRow_2();

	void fetchColumnTypes_();

	bool execOne_( );

	u_int_t columnPosition_(const tstring& columnName);
};

_jomoo_db_end

#endif // _DbQuery_SQLITE_H_
