
#ifndef _DbQuery_ODBC_H_
#define _DbQuery_ODBC_H_

# include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_db.h"
# define HAVE_ODBC_DRIVER

# include "DbQuery.h"
# include <map>
# include <vector>
# include <sql.h>

_jomoo_db_begin

class DbConnection_ODBC;

class DbQuery_ODBC : public DbQuery {
public:
	DbQuery_ODBC(DbConnection_ODBC* con, int timeout = 120);
	virtual ~DbQuery_ODBC();

	bool exec(const char* sql, size_t len, bool reportWarningsAsErrors = true );
	bool exec(const tstring& sql, bool reportWarningsAsErrors = true);
	bool nextRow();
	bool nextSet();
	int  columns();
	int columnType( size_t pos );
	const tchar* columnName( size_t pos );


	bool read(u_int_t column, bool& value);
	bool read(const tchar* column, bool& value);

	bool read(u_int_t column, int8_t& value);
	bool read(const tchar* column, int8_t& value);

	bool read(u_int_t column, int16_t& value);
	bool read(const tchar* column, int16_t& value);

	bool read(u_int_t column, int32_t& value);
	bool read(const tchar* column, int32_t& value);

	bool read(u_int_t column, int64_t& value);
	bool read(const tchar* column, int64_t& value);

	bool read(u_int_t column, Timestamp& value);
	bool read(const tchar* column, Timestamp& value);

	bool read(u_int_t column, double& value);
	bool read(const tchar* column, double& value);

	bool read(u_int_t column, char* buf, size_t& len );
	bool read(const tchar* columnName, char* buf, size_t& len );

	DECLARE_SHARED( );
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
	Timestamp		Time_;

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
