

#ifndef _DbConnection_Impl_H_
#define _DbConnection_Impl_H_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_db.h"
# include "spi/connection.h"
# include "jomoo/counter_ptr.hpp"
# include "jomoo/exception.hpp"
# include "jomoo/db/DbQuery.h"
# include "jomoo/db/DbCommand.h"

_jomoo_db_begin

class	DbQuery;
class	DbCommand;
class	DbTransaction;

class DbConnection
{
	friend class TransactionScope;

public:
	DbConnection( spi::connection* conn )
		: _connection( conn )
	{
		if( null_ptr != _connection )
			_connection->incRef();
	}

	~DbConnection()
	{
		release();
	}
	
	DbConnection( DbConnection& conn )
		: _connection( conn._connection )
	{
		if( null_ptr != _connection )
			_connection->incRef();
	}

	DbConnection& operator=( DbConnection& conn )
	{
		release();

		_connection = conn._connection;
		
		if( null_ptr != _connection )
			_connection->incRef();

		return *this;
	}

	void release()
	{
		if( null_ptr == _connection )
			return;
		_connection->decRef();
		_connection = null_ptr;
	}

	/**
	 * ����һ�����ݿ�����
	 * @param[ in ] parameters ���Ӳ���,һ����dsn�ַ���
	 * @param[ in ] len ���Ӳ����ַ����ĳ���,Ĭ��Ϊ-1��ʾ��֪�ж೤
	 */
	bool open(const tchar* parameters, size_t len = -1)
	{
		if( null_ptr == _connection )
			ThrowException( NullException );
		return _connection->open(parameters, len);
	}

	/**
	 * �ر����ݿ�����
	 */
	void close()
	{
		if( null_ptr == _connection )
			ThrowException( NullException );
		_connection->close();
	}

	/**
	 * ʹ����һ�����ݿ�
	 * @param[ in ] database ���ݿ�����
	 * @param[ in ] len ���ݿ������ַ����ĳ���,Ĭ��Ϊ-1��ʾ��֪�ж೤
	 */
	bool uses(const tchar* database, size_t len = -1)
	{
		if( null_ptr == _connection )
			ThrowException( NullException );
		return _connection->uses(database, len);
	}

	/**
	 * ����һ����ѯ����
	 */
	DbQuery createQuery();

	/**
	 * ����һ��ִ�ж���
	 */
	DbCommand createCommand();

	/**
	 * ��ʼһ������
	 */
	DbTransaction beginTransaction( IsolationLevel level );

	/**
	 * ȡ�����һ�δ���
	 */
	const tstring& last_error() const
	{
		if( null_ptr == _connection )
			ThrowException( NullException );
		return _connection->last_error();
	}

	/**
	 * ���ݿ�������
	 */
	const tstring& name() const
	{
		if( null_ptr == _connection )
			ThrowException( NullException );
		return _connection->name();
	}

private:
	spi::connection* _connection;
};

_jomoo_db_end

#endif // _DbConnection_Impl_H_
