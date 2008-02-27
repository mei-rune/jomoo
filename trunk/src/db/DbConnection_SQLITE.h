
#ifndef _DbConnection_SQLITE_
#define _DbConnection_SQLITE_


#define HAVE_DB_SQLITE

#include "DbConnection.h"
#include "Sqlite/Sqlite3.h"
#include "QSqlite.h"



_bt_begin

class DbConnection_SQLITE : public DbConnection
{
	friend class DbConnection;
	friend class DbQuery_SQLITE;
	friend class DbExecute_SQLITE;

public:
	virtual ~DbConnection_SQLITE();

	// Implements DbConnection
	virtual bool open(const tstring& parameters);
	virtual void close();
	virtual bool uses(const tstring& database);

	virtual PDbQuery query();
	virtual PDbExecute execute();

	virtual bool begin();
	virtual bool commit();
	virtual bool rollback();

	virtual const tstring& name() const;
	DbConnection_SQLITE(const tstring& name);

	const tstring& last_error() const;
private:

	tstring error_;
	tstring name_;

	sqlite3 *db_;
	const tstring& last_error(char *message);
	const tstring& last_error(sqlite3 *message);
	const tstring& last_error( const tstring& message);

};

_bt_end

#endif // _DbConnection_SQLITE_
