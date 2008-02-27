
#ifndef _SWORD_DB_DBTRANSACTION_
#define _SWORD_DB_DBTRANSACTION_

#include "DbConnection.h"

_bt_begin

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

_bt_end

#include "DbTransaction.inl"

#endif // _SWORD_DB_DBTRANSACTION_
