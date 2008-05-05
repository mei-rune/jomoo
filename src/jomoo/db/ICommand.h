
#ifndef _command_h_
#define _command_h_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_db.h"
# include "jomoo/counter_ptr.h"
# include "jomoo/datetime.h"
# include "jomoo/timespan.h"
# include "jomoo/Timestamp.h"

_jomoo_db_begin

namespace spi
{

class command : jomoo_shared
{
public:
	virtual ~command() {}

	/**
	 * 编译并执行sql语句
	 * @param[ in ] sql_string sql语句
	 * @param[ in ] len sql语句字符串的长度,默认为-1表示不知有多长
	 * @param[ in ] reportWarningsAsErrors 是否将警告当成错误
	 */
	virtual bool direct_exec( const tchar* sql_string, size_t len = -1 , bool reportWarningsAsErrors = true ) = 0;

	/**
	 * 编译sql语句
	 * @param[ in ] sql_string sql语句
	 * @param[ in ] len sql语句字符串的长度,默认为-1表示不知有多长
	 * @param[ in ] reportWarningsAsErrors 是否将警告当成错误
	 */
	virtual bool prepare( const tchar* sql_string, size_t len= -1, bool reportWarningsAsErrors = true ) = 0;

	/**
	 * 执行语句
	 */
	virtual bool exec( ) = 0;

	/**
	 * 清空内部变量,重新重始
	 */
	virtual bool reset( ) = 0;

	/**
	 * 所影响的行数
	 */
	virtual int affected_rows( ) = 0;

	/**
	 * 将值绑定到当前记录中指定的字段
	 * @param[ in ] column 字段在记录中的索引,从0开始
	 * @param[ out ] value 指定的值
	 * @exception OutOfRangeException 超出范围记录的列数
	 */
	virtual bool bind( int index, bool value ) = 0;

	/**
	 * 将值绑定到当前记录中指定的字段
	 * @param[ in ] column 字段在记录中的索引,从0开始
	 * @param[ out ] value 指定的值
	 * @exception OutOfRangeException 超出范围记录的列数
	 */
	virtual bool bind( int index, int8_t value ) = 0;

	/**
	 * 将值绑定到当前记录中指定的字段
	 * @param[ in ] column 字段在记录中的索引,从0开始
	 * @param[ out ] value 指定的值
	 * @exception OutOfRangeException 超出范围记录的列数
	 */
	virtual bool bind( int index, int16_t value ) = 0;

	/**
	 * 将值绑定到当前记录中指定的字段
	 * @param[ in ] column 字段在记录中的索引,从0开始
	 * @param[ out ] value 指定的值
	 * @exception OutOfRangeException 超出范围记录的列数
	 */
	virtual bool bind( int index, int32_t value ) = 0;

	/**
	 * 将值绑定到当前记录中指定的字段
	 * @param[ in ] column 字段在记录中的索引,从0开始
	 * @param[ out ] value 指定的值
	 * @exception OutOfRangeException 超出范围记录的列数
	 */
	virtual bool bind( int index, int64_t value ) = 0;

	/**
	 * 将值绑定到当前记录中指定的字段
	 * @param[ in ] column 字段在记录中的索引,从0开始
	 * @param[ out ] value 指定的值
	 * @exception OutOfRangeException 超出范围记录的列数
	 */
	virtual bool bind( int index, double value ) = 0;

	/**
	 * 将值绑定到当前记录中指定的字段
	 * @param[ in ] column 字段在记录中的索引,从0开始
	 * @param[ out ] value 指定的值
	 * @exception OutOfRangeException 超出范围记录的列数
	 */
	virtual bool bind( int index, const char* str , size_t n ) = 0;

	/**
	 * 将值绑定到当前记录中指定的字段
	 * @param[ in ] column 字段在记录中的索引,从0开始
	 * @param[ out ] value 指定的值
	 * @exception OutOfRangeException 超出范围记录的列数
	 */
	virtual bool bind( int index, const Timestamp& time ) = 0;

	/**
	 * 将值绑定到当前记录中指定的字段
	 * @param[ in ] columnName 列名
	 * @param[ out ] value 指定的值
	 * @exception IllegalArgumentException 没有找到列名为 columnName 的列
	 */
	virtual bool bind( const tchar* columnName, bool value ) = 0;

	/**
	 * 将值绑定到当前记录中指定的字段
	 * @param[ in ] columnName 列名
	 * @param[ out ] value 指定的值
	 * @exception IllegalArgumentException 没有找到列名为 columnName 的列
	 */
	virtual bool bind( const tchar* columnName, int8_t value ) = 0;

	/**
	 * 将值绑定到当前记录中指定的字段
	 * @param[ in ] columnName 列名
	 * @param[ out ] value 指定的值
	 * @exception IllegalArgumentException 没有找到列名为 columnName 的列
	 */
	virtual bool bind( const tchar* columnName, int16_t value ) = 0;

	/**
	 * 将值绑定到当前记录中指定的字段
	 * @param[ in ] columnName 列名
	 * @param[ out ] value 指定的值
	 * @exception IllegalArgumentException 没有找到列名为 columnName 的列
	 */
	virtual bool bind( const tchar* columnName, int32_t value ) = 0;

	/**
	 * 将值绑定到当前记录中指定的字段
	 * @param[ in ] columnName 列名
	 * @param[ out ] value 指定的值
	 * @exception IllegalArgumentException 没有找到列名为 columnName 的列
	 */
	virtual bool bind( const tchar* columnName, int64_t value ) = 0;

	/**
	 * 将值绑定到当前记录中指定的字段
	 * @param[ in ] columnName 列名
	 * @param[ out ] value 指定的值
	 * @exception IllegalArgumentException 没有找到列名为 columnName 的列
	 */
	virtual bool bind( const tchar* columnName, double value ) = 0;

	/**
	 * 将值绑定到当前记录中指定的字段
	 * @param[ in ] columnName 列名
	 * @param[ out ] value 指定的值
	 * @exception IllegalArgumentException 没有找到列名为 columnName 的列
	 */
	virtual bool bind( const tchar* columnName, const char* str , size_t n ) = 0;

	/**
	 * 将值绑定到当前记录中指定的字段
	 * @param[ in ] columnName 列名
	 * @param[ out ] value 指定的值
	 * @exception IllegalArgumentException 没有找到列名为 columnName 的列
	 */
	virtual bool bind( const tchar* columnName, const Timestamp& time ) = 0;
};

}

_jomoo_db_end

#endif // _command_h_
