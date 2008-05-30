
#ifndef _DbQuery_SQLITE_H_
#define _DbQuery_SQLITE_H_

# include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_db.h"
# include <vector>
# include "DbConnection_SQLITE.h"
# include "spi/query.h"

_jomoo_db_begin

namespace spi
{

class DbQuery_SQLITE : public query
{
public:
	DbQuery_SQLITE(DbConnection_SQLITE* con, int timeout = 120);
	virtual ~DbQuery_SQLITE();
  

	bool exec(const tchar* sql_string, size_t len, bool reportWarningsAsErrors = true );
	bool nextRow();
	bool nextSet();
	size_t  columns() const;
	int columnType( size_t pos ) const;
	const tchar* columnName( size_t pos ) const;

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

	bool readLength(u_int_t column, size_t& len );
	bool readLength(const tchar* columnName, size_t& len );

	void release();

	DECLARE_SHARED( );

private:
	DbConnection_SQLITE *_connection;

	const tchar* _pzTail;
	tstring _sql_string;
	sqlite3_stmt   *_stmt;

	bool         _firstRow;
	bool         _columnTypesReady;
	std::vector<columnItem> _columnItems;
	//variant _variant;

	bool fetchRow(bool isFirst);
	void fetchColumnTypes();
	bool prepare( );
	u_int_t columnPosition(const tstring& columnName);
	u_int_t columnPosition(const tchar* columnName);

	//static const tchar*[] _typeName;
};

}

_jomoo_db_end

#endif // _DbQuery_SQLITE_H_
