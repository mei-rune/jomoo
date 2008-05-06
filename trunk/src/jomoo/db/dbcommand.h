
#ifndef _DbExecute_h_
#define _DbExecute_h_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_db.h"
# include "jomoo/datetime.h"
# include "jomoo/timespan.h"
# include "jomoo/Timestamp.h"
# include "dbconnection.h"

_jomoo_db_begin

class DbCommand
{
public:
	explicit DbCommand(DbConnection& connection, spi::command* cmd )
		: _connection( connection )
		, _command( cmd )
	{
		if( null_ptr != _command )
			_command->incRef();
	}

	~DbCommand()
	{
		release();
	}
	
	explicit DbCommand( DbCommand& cmd )
		: _connection( cmd._connection )
		, _command( cmd._command )
	{
		if( null_ptr != _command )
			_command->incRef();
	}

	DbCommand& operator=( DbCommand& cmd )
	{
		release();

		_connection = cmd._connection;
		_command = cmd._command;
		
		if( null_ptr != _command )
			_command->incRef();

		return *this;
	}

	void release()
	{
		_connection.release();
		if( null_ptr == _command )
			return;
		_command->decRef();
		_command = null_ptr;
	}

	/**
	 * 获得数据库连接对象
	 */
    DbConnection& connection()
	{
		return _connection;
	}

	/**
	 * 编译并执行sql语句
	 * @param[ in ] sql_string sql语句
	 * @param[ in ] len sql语句字符串的长度,默认为-1表示不知有多长
	 * @param[ in ] reportWarningsAsErrors 是否将警告当成错误
	 */
	bool direct_exec( const tchar* sql_string, size_t len = -1 , bool reportWarningsAsErrors = true )
	{
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->direct_exec( sql_string, len, reportWarningsAsErrors );
	}

	/**
	 * 编译并执行sql语句
	 * @param[ in ] sql_string sql语句
	 * @param[ in ] reportWarningsAsErrors 是否将警告当成错误
	 */
	 bool direct_exec( const tstring& sql_string, bool reportWarningsAsErrors = true )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->direct_exec( sql_string.c_str(), sql_string.size(), reportWarningsAsErrors );
	 }

	/**
	 * 编译sql语句
	 * @param[ in ] sql_string sql语句
	 * @param[ in ] len sql语句字符串的长度,默认为-1表示不知有多长
	 * @param[ in ] reportWarningsAsErrors 是否将警告当成错误
	 */
	 bool prepare( const tchar* sql_string, size_t len= -1, bool reportWarningsAsErrors = true )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->prepare( sql_string, len, reportWarningsAsErrors );
	 }

	/**
	 * 编译sql语句
	 * @param[ in ] sql_string sql语句
	 * @param[ in ] reportWarningsAsErrors 是否将警告当成错误
	 */
	 bool prepare( const tstring& sql_string, bool reportWarningsAsErrors = true )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->prepare( sql_string.c_str(), sql_string.size(), reportWarningsAsErrors );
	 }

	/**
	 * 执行语句
	 */
	 bool exec( )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->exec( );
	 }

	/**
	 * 清空内部变量,重新重始
	 */
	 bool reset( )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->reset( );
	 }

	/**
	 * 所影响的行数
	 */
	 int affected_rows( )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->affected_rows( );
	 }

	/**
	 * 将值绑定到当前记录中指定的字段
	 * @param[ in ] column 字段在记录中的索引,从0开始
	 * @param[ out ] value 指定的值
	 * @exception OutOfRangeException 超出范围记录的列数
	 */
	 bool bind( int index, bool value )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->bind( index, value );
	 }

	/**
	 * 将值绑定到当前记录中指定的字段
	 * @param[ in ] column 字段在记录中的索引,从0开始
	 * @param[ out ] value 指定的值
	 * @exception OutOfRangeException 超出范围记录的列数
	 */
	 bool bind( int index, int8_t value )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->bind( index, value );
	 }

	/**
	 * 将值绑定到当前记录中指定的字段
	 * @param[ in ] column 字段在记录中的索引,从0开始
	 * @param[ out ] value 指定的值
	 * @exception OutOfRangeException 超出范围记录的列数
	 */
	 bool bind( int index, int16_t value )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->bind( index, value );
	 }

	/**
	 * 将值绑定到当前记录中指定的字段
	 * @param[ in ] column 字段在记录中的索引,从0开始
	 * @param[ out ] value 指定的值
	 * @exception OutOfRangeException 超出范围记录的列数
	 */
	 bool bind( int index, int32_t value )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->bind( index, value );
	 }

	/**
	 * 将值绑定到当前记录中指定的字段
	 * @param[ in ] column 字段在记录中的索引,从0开始
	 * @param[ out ] value 指定的值
	 * @exception OutOfRangeException 超出范围记录的列数
	 */
	 bool bind( int index, int64_t value )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->bind( index, value );
	 }

	/**
	 * 将值绑定到当前记录中指定的字段
	 * @param[ in ] column 字段在记录中的索引,从0开始
	 * @param[ out ] value 指定的值
	 * @exception OutOfRangeException 超出范围记录的列数
	 */
	 bool bind( int index, double value )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->bind( index, value );
	 }

	/**
	 * 将值绑定到当前记录中指定的字段
	 * @param[ in ] column 字段在记录中的索引,从0开始
	 * @param[ out ] value 指定的值
	 * @exception OutOfRangeException 超出范围记录的列数
	 */
	 bool bind( int index, const char* str , size_t n )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->bind( index, str, n );
	 }

	/**
	 * 将值绑定到当前记录中指定的字段
	 * @param[ in ] column 字段在记录中的索引,从0开始
	 * @param[ out ] value 指定的值
	 * @exception OutOfRangeException 超出范围记录的列数
	 */
	 bool bind( int index, const Timestamp& time )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->bind( index, time );
	 }

	/**
	 * 将值绑定到当前记录中指定的字段
	 * @param[ in ] columnName 列名
	 * @param[ out ] value 指定的值
	 * @exception IllegalArgumentException 没有找到列名为 columnName 的列
	 */
	 bool bind( const tchar* columnName, bool value )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->bind( columnName, value );
	 }

	/**
	 * 将值绑定到当前记录中指定的字段
	 * @param[ in ] columnName 列名
	 * @param[ out ] value 指定的值
	 * @exception IllegalArgumentException 没有找到列名为 columnName 的列
	 */
	 bool bind( const tchar* columnName, int8_t value )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->bind( columnName, value );
	 }

	/**
	 * 将值绑定到当前记录中指定的字段
	 * @param[ in ] columnName 列名
	 * @param[ out ] value 指定的值
	 * @exception IllegalArgumentException 没有找到列名为 columnName 的列
	 */
	 bool bind( const tchar* columnName, int16_t value )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->bind( columnName, value );
	 }

	/**
	 * 将值绑定到当前记录中指定的字段
	 * @param[ in ] columnName 列名
	 * @param[ out ] value 指定的值
	 * @exception IllegalArgumentException 没有找到列名为 columnName 的列
	 */
	 bool bind( const tchar* columnName, int32_t value )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->bind( columnName, value );
	 }

	/**
	 * 将值绑定到当前记录中指定的字段
	 * @param[ in ] columnName 列名
	 * @param[ out ] value 指定的值
	 * @exception IllegalArgumentException 没有找到列名为 columnName 的列
	 */
	 bool bind( const tchar* columnName, int64_t value )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->bind( columnName, value );
	 }

	/**
	 * 将值绑定到当前记录中指定的字段
	 * @param[ in ] columnName 列名
	 * @param[ out ] value 指定的值
	 * @exception IllegalArgumentException 没有找到列名为 columnName 的列
	 */
	 bool bind( const tchar* columnName, double value )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->bind( columnName, value );
	 }

	/**
	 * 将值绑定到当前记录中指定的字段
	 * @param[ in ] columnName 列名
	 * @param[ out ] value 指定的值
	 * @exception IllegalArgumentException 没有找到列名为 columnName 的列
	 */
	 bool bind( const tchar* columnName, const char* str , size_t n )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->bind( columnName, str, n );
	 }

	/**
	 * 将值绑定到当前记录中指定的字段
	 * @param[ in ] columnName 列名
	 * @param[ out ] value 指定的值
	 * @exception IllegalArgumentException 没有找到列名为 columnName 的列
	 */
	 bool bind( const tchar* columnName, const Timestamp& time )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->bind( columnName, value );
	 }

private:
	spi::command* _command;
	DbConnection _connection;
};


_jomoo_db_end

#endif // _DbExecute_h_
