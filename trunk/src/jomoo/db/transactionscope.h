
#ifndef _TransactionScope_
#define _TransactionScope_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_db.h"
#include "DbConnection.h"

_jomoo_db_begin

class TransactionScope
{
public:
	explicit TransactionScope( DbConnection& connection )
		: _connection( connection )
		, _transaction( 0 )
	{
			_transaction = connection.beginTransaction( Unspecified );
	}
	
	TransactionScope( DbConnection& connection, IsolationLevel l)
		: _connection( connection )
		, _transaction( 0 )
	{
			_transaction = connection.beginTransaction( l );
	}
	
	TransactionScope( DbConnection& connection, spi::transaction* tr)
		: _connection( connection )
		, _transaction( tr )
	{
		if( null_ptr == _transaction )
			ThrowException( NullException );
	}

	~TransactionScope()
	{
		if( !rollback() )
			ThrowException1( DbException, _connection.last_error() );
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
		if( null_ptr == _transaction ) return Unspecified;

		return _transaction->level();
	}

	/**
	 * �ύ����
	 */
	bool commit()
	{
		if( null_ptr == _transaction ) return true;

		return _connection->commitTransaction( _transaction );
	}

	/**
	 * �ع�����
	 */
	bool rollback()
	{
		if( null_ptr == _transaction ) return true;

		return _connection->rollbackTransaction( _transaction );
	}

protected:
	DECLARE_NO_COPY_CLASS( TransactionScope );
	DbConnection _connection;
	spi::transaction* _transaction;
};

_jomoo_db_end

#endif // _TransactionScope_
