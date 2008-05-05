
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

class DbTransaction
{
public:
	DbTransaction( DbConnection& connection, spi::transaction* tr)
		: _connection( connection )
		, _transaction( tr )
	{
		if( null_ptr != _transaction)
			_transaction->incRef();
	}

	~DbTransaction()
	{
		rollback();
	}

	/**
	 * ������ݿ����Ӷ���
	 */
    DbConnection& connection()
	{
		return _connection;
	}

	/**
	 * ȡ�õ������ IsolationLevel
	 */
	IsolationLevel level() const
	{
		if( null_ptr == _transaction )
			ThrowException( NullException );
		return _transaction->level();
	}

	/**
	 * �ύ����
	 */
	bool commit()
	{
		if( null_ptr == _transaction )
			ThrowException( NullException );
		return _connection->commitTransaction( _transaction );
	}

	/**
	 * �ع�����
	 */
	bool rollback()
	{
		if( null_ptr == _transaction )
			ThrowException( NullException );
		return _connection->rollbackTransaction( _transaction );
	}

protected:
	DECLARE_NO_COPY_CLASS( DbTransaction );
	DbConnection _connection;
	spi::transaction* _transaction;
};

_jomoo_db_end

#endif // _SWORD_DB_DBTRANSACTION_
