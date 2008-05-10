
#ifndef _DbConnection_ODBC_
#define _DbConnection_ODBC_

# include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_db.h"
# include "spi/connection.h"
# include <sql.h>
# include <sqlext.h>

#define SQLERROR(r) (r!=SQL_SUCCESS && r!=SQL_SUCCESS_WITH_INFO)

_jomoo_db_begin

namespace spi
{

class DbTransaction_ODBC;
class DbTransaction_ODBC;

class DbConnection_ODBC : public connection
{
public:
	DbConnection_ODBC(const tstring& name);
	~DbConnection_ODBC();

	// Implements DbConnection
	bool open(const tchar* parameters, size_t len);
	void close();
	bool uses(const tchar* database, size_t len);
	
	query* createQuery();
	command* createCommand();
	transaction* beginTransaction( IsolationLevel level );

	const tstring& name() const;
	const tstring& last_error( ) const;

	DECLARE_SHARED( );
private:

	friend class DbTransaction_ODBC;

	void reportError_(const tstring& message, SQLSMALLINT handleType, SQLHANDLE handle);
	bool autoCommit_(bool on);

	const tstring& last_error( const tstring& message );

	bool    active_;
	SQLHENV dbe_;
	SQLHDBC dbc_;

	tstring error_;
	tstring name_;
};

}

_jomoo_db_end

#endif // _DbConnection_ODBC_
