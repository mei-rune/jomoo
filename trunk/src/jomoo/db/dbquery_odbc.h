
#ifndef _DbQuery_ODBC_H_
#define _DbQuery_ODBC_H_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_db.h"
#define HAVE_DB_ODBC

#include "DbQuery.h"
#include <map>
#include <vector>
#include <sql.h>

_jomoo_db_begin

class DbConnection_ODBC;

class DbQuery_ODBC : public DbQuery2 {
public:
	DbQuery_ODBC(DbConnection_ODBC* con, int timeout = 120);
	virtual ~DbQuery_ODBC();

	virtual bool exec(const char* sql, size_t len, bool reportWarningsAsErrors = true );
	virtual bool exec(const tstring& sql, bool reportWarningsAsErrors = true);
	virtual bool nextRow();
	virtual bool nextSet();
	virtual int  columns();


	virtual const Variant&     get(u_int_t column);
	virtual const Variant&     get(const tstring& column);


	bool getBoolean(u_int_t column);
	bool getBoolean(const tstring& column);
	int getInt(u_int_t column);
	int getInt(const tstring& column);
	__int64 getInt64(u_int_t column);
	__int64 getInt64(const tstring& column);
	double getDouble(u_int_t column);
	double getDouble(const tstring& column);
	const tstring& getString(u_int_t column);
	const tstring& getString(const tstring& column);
#ifdef _BOOST_TIME_
	const ptime& getTime(u_int_t column);
	const ptime& getTime(const tstring& column);
#endif
	int getColumnType( size_t pos );
	const tstring& getColumnName( size_t pos );

private:
	DbConnection_ODBC* con_;
	SQLHSTMT           dbs_;
	int                columns_;
	// columns type description
	typedef std::vector<Variant_Type::Type > ColumnTypes;
	ColumnTypes        columnTypes_;
	bool               columnTypesReady_;
	// columns names
	typedef std::vector<tstring> ColumnNames;
	ColumnNames        columnNames_;
	typedef std::map<tstring, u_int_t> ColumnPositions;
	ColumnPositions    columnPositions_;
	
	// 
	tstring		String_;
#ifdef _BOOST_TIME_
	ptime		Time_;
#endif

	// row data
	typedef std::vector<Variant> RowData;
	RowData            row_;
	bool               rowReady_;
	// error handling
	bool errorThrown_;

	void reportError_(const tstring& message);
	bool firstRow_();
	bool nextSet_();

	void fetchRow_();
	void fetchColumnTypes_();

	u_int_t columnPosition_(const tstring& columnName);
};

_jomoo_db_end

#endif // _DbQuery_ODBC_H_
