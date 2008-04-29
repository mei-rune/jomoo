
#ifndef _DbQuery_H_
#define _DbQuery_H_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_db.h"
# include "jomoo/datetime.h"
# include "jomoo/timespan.h"
# include "jomoo/Timestamp.h"

_jomoo_db_begin

class DbQuery {
public:
	virtual ~DbQuery() {}

	virtual bool exec(const char* sql, size_t len, bool reportWarningsAsErrors = true ) = 0;
	virtual bool exec(const tstring& sql, bool reportWarningsAsErrors = true ) = 0;
	virtual bool nextRow() = 0;
	virtual bool nextSet() = 0;
	virtual int columns() = 0;
	virtual int getColumnType( size_t pos ) = 0;
	virtual const tstring& getColumnName( size_t pos ) = 0;

	virtual bool getBoolean(u_int_t column) = 0;
	virtual bool getBoolean(const tstring& column) = 0;
	virtual bool getBoolean(const tchar* column) = 0;
	virtual int getInt(u_int_t column) = 0;
	virtual int getInt(const tstring& column) = 0;
	virtual int getInt(const tchar* column) = 0;
	virtual __int64 getInt64(u_int_t column) = 0;
	virtual __int64 getInt64(const tstring& column) = 0;
	virtual __int64 getInt64(const tchar* column) = 0;
	virtual double getDouble(u_int_t column) = 0;
	virtual double getDouble(const tstring& column) = 0;
	virtual double getDouble(const tchar* column) = 0;
	virtual const tstring& getString(u_int_t column) = 0;
	virtual const tstring& getString(const tstring& column) = 0;
	virtual const tstring& getString(const tchar* column) = 0;
	virtual const Timestamp& getTimestamp(u_int_t column) = 0;
	virtual const Timestamp& getTimestamp(const tstring& column) = 0;
	virtual const Timestamp& getTimestamp(const tchar* column) = 0;

	virtual void incRef() = 0;
    virtual void decRef() = 0;
};

_jomoo_db_end

#endif // _DbQuery_H_
