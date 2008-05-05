

#ifndef _DbConnection_H_
#define _DbConnection_H_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_db.h"
# include "jomoo/counter_ptr.hpp"
# include "jomoo/exception.hpp"

_jomoo_db_begin

class DbConnection : jomoo_shared
{
public:
	explicit DbConnection( spi::connection* conn )
		: _connection( conn )
	{
		if( null_ptr != _connection )
			_connection->incRef();
	}

	~DbConnection()
	{
		release();
	}
	
	explicit DbConnection( DbConnection& conn )
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
	DbQuery query()
	{
		if( null_ptr == _connection )
			ThrowException( NullException );
		return DbQuery( _connection->query() );
	}

	/**
	 * 创建一个执行对象
	 */
	DbCommand execute()
	{
		if( null_ptr == _connection )
			ThrowException( NullException );
		return DbCommand( _connection->execute() );
	}

	/**
	 * 开始一个事务
	 */
	DbTransaction beginTransaction( IsolationLevel level )
	{
		if( null_ptr == _connection )
			ThrowException( NullException );
		return DbTransaction( _connection->beginTransaction(level) );
	}

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

#endif // _DbConnection_H_
