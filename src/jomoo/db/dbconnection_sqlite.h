
#ifndef _DbConnection_SQLITE_
#define _DbConnection_SQLITE_

# include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "jomoo/db/config_db.h"
# include "jomoo/db/spi/connection.h"
# include "sqlite_wrapper.h"

_jomoo_db_begin

namespace spi
{

class DbConnection_SQLITE : public connection
{
public:
	DbConnection_SQLITE(const tstring& name);
	~DbConnection_SQLITE();

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

	friend class DbCommand_SQLITE;
	friend class DbQuery_SQLITE;
	friend class DbTransaction_SQLITE;

	tstring error_;
	tstring name_;

	sqlite3 *db_;
	const tstring& last_error(char *message);
	const tstring& last_error(sqlite3 *message);
	const tstring& last_error( const tstring& message);

};

}

_jomoo_db_end

#endif // _DbConnection_SQLITE_
