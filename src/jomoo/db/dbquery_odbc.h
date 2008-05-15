
#ifndef _DbQuery_ODBC_H_
#define _DbQuery_ODBC_H_

# include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_db.h"
# include "spi/query.h"
# include "DbConnection_ODBC.h"
# include <map>
# include <vector>
# include <sql.h>

_jomoo_db_begin

namespace spi
{

union variant
{
public:	
	bool bool_value;
	int8_t int8_value;
	int16_t int16_value;
	int32_t int32_value;
	int64_t int64_value;
	Timestamp time_stamp;
	Timespan time_span;
	StringPtr<char> stringPtr;
};

class DbQuery_ODBC : public query
{
public:
	DbQuery_ODBC(DbConnection_ODBC* con, int timeout = 120);
	virtual ~DbQuery_ODBC();  

	bool exec(const tchar* sql_string, size_t len, bool reportWarningsAsErrors = true );
	bool nextRow();
	bool nextSet();
	int  columns();
	int columnType( size_t pos );
	const tchar* columnName( size_t pos );

	bool read(u_int_t column, bool& value);
	bool read(const tchar* columnName, bool& value);

	bool read(u_int_t column, int8_t& value);
	bool read(const tchar* columnName, int8_t& value);

	bool read(u_int_t column, int16_t& value);
	bool read(const tchar* columnName, int16_t& value);

	bool read(u_int_t column, int32_t& value);
	bool read(const tchar* columnName, int32_t& value);

	bool read(u_int_t column, int64_t& value);
	bool read(const tchar* columnName, int64_t& value);

	bool read(u_int_t column, Timestamp& value);
	bool read(const tchar* columnName, Timestamp& value);

	bool read(u_int_t column, Timespan& value);
	bool read(const tchar* columnName, Timespan& value);

	bool read(u_int_t column, double& value);
	bool read(const tchar* columnName, double& value);

	int read(u_int_t column, char* buf, size_t& len );
	int read(const tchar* columnName, char* buf, size_t& len );

	int readBLOB(u_int_t column, void* buf, size_t& len );
	int readBLOB(const tchar* columnName, void* buf, size_t& len );

	bool readLenght(u_int_t column, size_t& len );
	bool readLenght(const tchar* columnName, size_t& len );

	void release();

	DECLARE_SHARED( );
private:
	DbConnection_ODBC* con_;
	SQLHSTMT           dbs_;
	int                columns_;
	// columns type description
	typedef std::vector<DBType> ColumnTypes;
	typedef std::vector<tstring> ColumnNames;
	typedef stdext::hash_map<tstring, u_int_t> ColumnPositions;

	ColumnTypes        columnTypes_;
	bool               columnTypesReady_;
	// columns names
	ColumnNames        columnNames_;
	ColumnPositions    columnPositions_;

	// row data
	std::vector<variant> row_;
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

}

_jomoo_db_end

#endif // _DbQuery_ODBC_H_
