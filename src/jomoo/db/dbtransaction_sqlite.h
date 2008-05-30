
#ifndef _DbTransaction_SQLITE_
#define _DbTransaction_SQLITE_

# include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_db.h"
# include "jomoo/db/spi/transaction.h"
# include "DbConnection_SQLITE.h"

_jomoo_db_begin

namespace spi
{

class DbTransaction_SQLITE : public transaction
{
public:

	DbTransaction_SQLITE(DbConnection_SQLITE* conn, IsolationLevel level);
	
	~DbTransaction_SQLITE();

	void release();

	bool beginTransaction( IsolationLevel level );

	IsolationLevel level() const;

	bool commit();

	bool rollback();

private:
	DbConnection_SQLITE* _conn;
	IsolationLevel _level;
};

}

_jomoo_db_end

#endif // _DbConnection_ODBC_
