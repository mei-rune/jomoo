
#ifndef _DbQuery_SQLITE_H_
#define _DbQuery_SQLITE_H_

#define HAVE_DB_SQLITE

#include "sqlite/sqlite3.h"
#include "QSqlite.h"
#include "DbQuery.h"

_bt_begin

class DbConnection_SQLITE;

class DbQuery_SQLITE : public DbQuery
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
	const ptime& getTime(u_int column);
	const ptime& getTime(const tstring& column);

private:
	DbConnection_SQLITE *con_;

	const tchar* tail_;
	//
	sqlite3_stmt   *stmt_;
	// row data
	Variant            result_;
	tstring		String_;
	ptime		Time_;

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

	void fetchColumnTypes_();

	bool execOne_( );

	u_int_t columnPosition_(const tstring& columnName);
};

_bt_end

#endif // _DbQuery_SQLITE_H_
