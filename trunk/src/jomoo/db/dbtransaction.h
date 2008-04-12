
#ifndef _SWORD_DB_DBTRANSACTION_
#define _SWORD_DB_DBTRANSACTION_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_db.h"
#include "DbConnection.h"

_jomoo_db_begin

class DbTransaction {
public:
	DbTransaction(PDbConnection db);
	~DbTransaction();

	void commit();
	void rollback();

protected:
	PDbConnection db_;
	bool finished_;
};

_jomoo_db_end

#include "DbTransaction.inl"

#endif // _SWORD_DB_DBTRANSACTION_
