
#ifndef _DbQuery_H_
#define _DbQuery_H_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_db.h"
# include "jomoo/exception.hpp"
# include "jomoo/datetime.h"
# include "jomoo/timespan.h"
# include "jomoo/Timestamp.h"
# include "spi/query.h"

_jomoo_db_begin

class DbQuery
{
public:
	DbQuery( spi::query* q )
		: _query( q )
	{
		if( null_ptr != _query )
			_query->incRef();
	}

	~DbQuery()
	{
		release();
	}
	
	DbQuery( DbQuery& q )
		: _query( q._query )
	{
		if( null_ptr != _query )
			_query->incRef();
	}

	DbQuery& operator=( DbQuery& q )
	{
		release();

		_query = q._query;
		
		if( null_ptr != _query )
			_query->incRef();

		return *this;
	}

	void release()
	{
		if( null_ptr == _query )
			return;

		_query->decRef();
		_query = null_ptr;
	}

	/**
	 * 执行sql语句
	 * @param[ in ] sql_string sql语句
	 * @param[ in ] len sql语句的长度,默认为-1表示不知道有多长
	 * @param[ in ] reportWarningsAsErrors 是否将警告当成错误
	 */
	bool exec(const tchar* sql_string, size_t len = -1, bool reportWarningsAsErrors = true )
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->exec( sql_string, len, reportWarningsAsErrors);
	}

	/**
	 * 执行sql语句
	 * @param[ in ] sql sql语句
	 * @param[ in ] reportWarningsAsErrors 是否将警告当成错误
	 */
	bool exec(const tstring& sql, bool reportWarningsAsErrors = true )
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->exec( sql.c_str(), sql.size(), reportWarningsAsErrors);
	}

	/**
	 * 切换到下一个记录
	 */
	bool nextRow()
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->nextRow( );
	}

	/**
	 * 切换到下一记录集
	 */
	bool nextSet()
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->nextSet( );
	}

	/**
	 * 取得当前结果共有多少列
	 */
	int columns()
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->columns( );
	}

	/**
	 * 取得指定列的数据类型,请见枚举 DBType
	 * @see DBType
	 * @exception OutOfRangeException 超出范围记录的列数
	 */
	int columnType( size_t pos )
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->columnType( pos );
	}

	/**
	 * 取得指定列的列名
	 * @exception OutOfRangeException 超出范围记录的列数
	 */
	const tchar* columnName( size_t pos )
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->columnName( pos );
	}

	/**
	 * 从当前记录中读取指定列的值
	 * @param[ in ] column 列在记录中的索引,从0开始
	 * @param[ out ] value 读取的值
	 * @exception OutOfRangeException 超出范围记录的列数
	 */
	bool read(u_int_t column, bool& value)
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->read( column, value );
	}

	/**
	 * 从当前记录中读取指定列名的值
	 * @param[ in ] columnName 列名
	 * @param[ out ] value 读取的值
	 * @exception IllegalArgumentException 没有找到列名为 columnName 的列
	 */
	bool read(const tchar* columnName, bool& value)
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->read( columnName, value );
	}

	/**
	 * 从当前记录中读取指定列的值
	 * @param[ in ] column 列在记录中的索引,从0开始
	 * @param[ out ] value 读取的值
	 * @exception OutOfRangeException 超出范围记录的列数
	 */
	bool read(u_int_t column, int8_t& value)
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->read( column, value );
	}
	/**
	 * 从当前记录中读取指定列名的值
	 * @param[ in ] columnName 列名
	 * @param[ out ] value 读取的值
	 * @exception IllegalArgumentException 没有找到列名为 columnName 的列
	 */
	bool read(const tchar* columnName, int8_t& value)
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->read( columnName, value );
	}

	/**
	 * 从当前记录中读取指定列的值
	 * @param[ in ] column 列在记录中的索引,从0开始
	 * @param[ out ] value 读取的值
	 * @exception OutOfRangeException 超出范围记录的列数
	 */
	bool read(u_int_t column, int16_t& value)
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->read( column, value );
	}
	/**
	 * 从当前记录中读取指定列名的值
	 * @param[ in ] columnName 列名
	 * @param[ out ] value 读取的值
	 * @exception IllegalArgumentException 没有找到列名为 columnName 的列
	 */
	bool read(const tchar* columnName, int16_t& value)
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->read( columnName, value );
	}

	/**
	 * 从当前记录中读取指定列的值
	 * @param[ in ] column 列在记录中的索引,从0开始
	 * @param[ out ] value 读取的值
	 * @exception OutOfRangeException 超出范围记录的列数
	 */
	bool read(u_int_t column, int32_t& value)
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->read( column, value );
	}
	/**
	 * 从当前记录中读取指定列名的值
	 * @param[ in ] columnName 列名
	 * @param[ out ] value 读取的值
	 * @exception IllegalArgumentException 没有找到列名为 columnName 的列
	 */
	bool read(const tchar* columnName, int32_t& value)
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->read( columnName, value );
	}

	/**
	 * 从当前记录中读取指定列的值
	 * @param[ in ] column 列在记录中的索引,从0开始
	 * @param[ out ] value 读取的值
	 * @exception OutOfRangeException 超出范围记录的列数
	 */
	bool read(u_int_t column, int64_t& value)
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->read( column, value );
	}
	/**
	 * 从当前记录中读取指定列名的值
	 * @param[ in ] columnName 列名
	 * @param[ out ] value 读取的值
	 * @exception IllegalArgumentException 没有找到列名为 columnName 的列
	 */
	bool read(const tchar* columnName, int64_t& value)
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->read( columnName, value );
	}

	/**
	 * 从当前记录中读取指定列的值
	 * @param[ in ] column 列在记录中的索引,从0开始
	 * @param[ out ] value 读取的值
	 * @exception OutOfRangeException 超出范围记录的列数
	 */
	bool read(u_int_t column, Timestamp& value)
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->read( column, value );
	}

	/**
	 * 从当前记录中读取指定列名的值
	 * @param[ in ] columnName 列名
	 * @param[ out ] value 读取的值
	 * @exception IllegalArgumentException 没有找到列名为 columnName 的列
	 */
	bool read(const tchar* columnName, Timestamp& value)
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->read( columnName, value );
	}

	/**
	 * 从当前记录中读取指定列的值
	 * @param[ in ] column 列在记录中的索引,从0开始
	 * @param[ out ] value 读取的值
	 * @exception OutOfRangeException 超出范围记录的列数
	 */
	bool read(u_int_t column, double& value)
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->read( column, value );
	}

	/**
	 * 从当前记录中读取指定列名的值
	 * @param[ in ] columnName 列名
	 * @param[ out ] value 读取的值
	 * @exception IllegalArgumentException 没有找到列名为 columnName 的列
	 */
	bool read(const tchar* columnName, double& value)
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->read( columnName, value );
	}

	/**
	 * 从当前记录中读取指定列的值
	 * @param[ in ] column 列在记录中的索引,从0开始
	 * @param[ out ] value 读取的值
	 * @exception OutOfRangeException 超出范围记录的列数
	 */
	bool read(u_int_t column, char* buf, size_t& len )
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->read( column, buf, len );
	}

	/**
	 * 从当前记录中读取指定列名的值
	 * @param[ in ] columnName 列名
	 * @param[ out ] value 读取的值
	 * @exception IllegalArgumentException 没有找到列名为 columnName 的列
	 */
	bool read(const tchar* columnName, char* buf, size_t& len )
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->read( columnName, buf, len );
	}

private:
	spi::query* _query;
};

_jomoo_db_end

#endif // _DbQuery_H_
