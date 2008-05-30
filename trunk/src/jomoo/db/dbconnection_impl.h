

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
	 * 创建一个数据库连接
	 * @param[ in ] parameters 连接参数,一般是dsn字符串
	 * @param[ in ] len 连接参数字符串的长度,默认为-1表示不知有多长
	 */
	bool open(const tchar* parameters, size_t len = -1)
	{
		if( null_ptr == _connection )
			ThrowException( NullException );
		return _connection->open(parameters, len);
	}

	/**
	 * 关闭数据库连接
	 */
	void close()
	{
		if( null_ptr == _connection )
			ThrowException( NullException );
		_connection->close();
	}

	/**
	 * 使用另一个数据库
	 * @param[ in ] database 数据库名字
	 * @param[ in ] len 数据库名字字符串的长度,默认为-1表示不知有多长
	 */
	bool uses(const tchar* database, size_t len = -1)
	{
		if( null_ptr == _connection )
			ThrowException( NullException );
		return _connection->uses(database, len);
	}

	/**
	 * 创建一个查询对象
	 */
	DbQuery createQuery();

	/**
	 * 创建一个执行对象
	 */
	DbCommand createCommand();

	/**
	 * 开始一个事务
	 */
	DbTransaction beginTransaction( IsolationLevel level );

	/**
	 * 取得最后一次错误
	 */
	const tstring& last_error() const
	{
		if( null_ptr == _connection )
			ThrowException( NullException );
		return _connection->last_error();
	}

	/**
	 * 数据库连接名
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
