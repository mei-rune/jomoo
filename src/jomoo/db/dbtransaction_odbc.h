
#ifndef _DbTransaction_ODBC_
#define _DbTransaction_ODBC_

# include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_db.h"
# include "DbConnection_ODBC.h"
# include "spi/transaction.h"

_jomoo_db_begin

namespace spi
{

class DbTransaction_ODBC : transaction
{
public:

	DbTransaction_ODBC(DbConnection_ODBC* odbc, IsolationLevel level);
	
	~DbTransaction_ODBC();

	void release();

	bool beginTransaction( IsolationLevel level );

	IsolationLevel level() const;

	bool commit();

	bool rollback();

private:
	DbConnection_ODBC* _odbc;
	IsolationLevel _level;
};

}

_jomoo_db_end

#endif // _DbConnection_ODBC_
