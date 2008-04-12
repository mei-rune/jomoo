


_jomoo_db_begin

inline DbTransaction::DbTransaction(PDbConnection db) : db_(db), finished_(false)
{
	db_->begin();
}

inline DbTransaction::~DbTransaction()
{
	if (!finished_)
		rollback();
}

inline void DbTransaction::commit()
{
	db_->commit();
	finished_ = true;
}

inline void DbTransaction::rollback()
{
	db_->rollback();
	finished_ = true;
}

_jomoo_db_end
