
#ifndef _DbConnection_ODBC_
#define _DbConnection_ODBC_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_db.h"
#define HAVE_DB_ODBC
#include "DbConnection.h"
#include <sql.h>
#include <sqlext.h>

#define SQLERROR(r) (r!=SQL_SUCCESS && r!=SQL_SUCCESS_WITH_INFO)

_jomoo_db_begin

class DbConnection_ODBC : public DbConnection2
{
	friend class DbConnection;
	friend class DbQuery_ODBC;
	friend class DbExecute_ODBC;

public:
	virtual ~DbConnection_ODBC();

	// Implements DbConnection
	virtual bool open(const tstring& parameters);
	virtual void close();
	virtual bool uses(const tstring& database);
	
	virtual PDbQuery query();
	virtual PDbExecute execute();

	virtual PDbQuery2 query2();
	virtual PDbExecute2 execute2();

	virtual bool begin();
	virtual bool commit();
	virtual bool rollback();

	virtual const tstring& name() const;

	DbConnection_ODBC(const tstring& name);

	bool    active_;
	SQLHENV dbe_;
	SQLHDBC dbc_;

	const tstring& last_error( ) const;

private:

	void reportError_(const tstring& message, SQLSMALLINT handleType, SQLHANDLE handle);
	bool autoCommit_(bool on);

	const tstring& last_error( const tstring& message );

	tstring error_;
	tstring name_;
};

_jomoo_db_end

#endif // _DbConnection_ODBC_
