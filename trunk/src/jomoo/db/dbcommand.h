
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
	 * ������ݿ����Ӷ���
	 */
    DbConnection& connection()
	{
		return _connection;
	}

	/**
	 * ���벢ִ��sql���
	 * @param[ in ] sql_string sql���
	 * @param[ in ] len sql����ַ����ĳ���,Ĭ��Ϊ-1��ʾ��֪�ж೤
	 * @param[ in ] reportWarningsAsErrors �Ƿ񽫾��浱�ɴ���
	 */
	bool direct_exec( const tchar* sql_string, size_t len = -1 , bool reportWarningsAsErrors = true )
	{
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->direct_exec( sql_string, len, reportWarningsAsErrors );
	}

	/**
	 * ���벢ִ��sql���
	 * @param[ in ] sql_string sql���
	 * @param[ in ] reportWarningsAsErrors �Ƿ񽫾��浱�ɴ���
	 */
	 bool direct_exec( const tstring& sql_string, bool reportWarningsAsErrors = true )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->direct_exec( sql_string.c_str(), sql_string.size(), reportWarningsAsErrors );
	 }

	/**
	 * ����sql���
	 * @param[ in ] sql_string sql���
	 * @param[ in ] len sql����ַ����ĳ���,Ĭ��Ϊ-1��ʾ��֪�ж೤
	 * @param[ in ] reportWarningsAsErrors �Ƿ񽫾��浱�ɴ���
	 */
	 bool prepare( const tchar* sql_string, size_t len= -1, bool reportWarningsAsErrors = true )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->prepare( sql_string, len, reportWarningsAsErrors );
	 }

	/**
	 * ����sql���
	 * @param[ in ] sql_string sql���
	 * @param[ in ] reportWarningsAsErrors �Ƿ񽫾��浱�ɴ���
	 */
	 bool prepare( const tstring& sql_string, bool reportWarningsAsErrors = true )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->prepare( sql_string.c_str(), sql_string.size(), reportWarningsAsErrors );
	 }

	/**
	 * ִ�����
	 */
	 bool exec( )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->exec( );
	 }

	/**
	 * ����ڲ�����,������ʼ
	 */
	 bool reset( )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->reset( );
	 }

	/**
	 * ��Ӱ�������
	 */
	 int affected_rows( )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->affected_rows( );
	 }

	/**
	 * ��ֵ�󶨵���ǰ��¼��ָ�����ֶ�
	 * @param[ in ] column �ֶ��ڼ�¼�е�����,��0��ʼ
	 * @param[ out ] value ָ����ֵ
	 * @exception OutOfRangeException ������Χ��¼������
	 */
	 bool bind( int index, bool value )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->bind( index, value );
	 }

	/**
	 * ��ֵ�󶨵���ǰ��¼��ָ�����ֶ�
	 * @param[ in ] column �ֶ��ڼ�¼�е�����,��0��ʼ
	 * @param[ out ] value ָ����ֵ
	 * @exception OutOfRangeException ������Χ��¼������
	 */
	 bool bind( int index, int8_t value )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->bind( index, value );
	 }

	/**
	 * ��ֵ�󶨵���ǰ��¼��ָ�����ֶ�
	 * @param[ in ] column �ֶ��ڼ�¼�е�����,��0��ʼ
	 * @param[ out ] value ָ����ֵ
	 * @exception OutOfRangeException ������Χ��¼������
	 */
	 bool bind( int index, int16_t value )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->bind( index, value );
	 }

	/**
	 * ��ֵ�󶨵���ǰ��¼��ָ�����ֶ�
	 * @param[ in ] column �ֶ��ڼ�¼�е�����,��0��ʼ
	 * @param[ out ] value ָ����ֵ
	 * @exception OutOfRangeException ������Χ��¼������
	 */
	 bool bind( int index, int32_t value )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->bind( index, value );
	 }

	/**
	 * ��ֵ�󶨵���ǰ��¼��ָ�����ֶ�
	 * @param[ in ] column �ֶ��ڼ�¼�е�����,��0��ʼ
	 * @param[ out ] value ָ����ֵ
	 * @exception OutOfRangeException ������Χ��¼������
	 */
	 bool bind( int index, int64_t value )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->bind( index, value );
	 }

	/**
	 * ��ֵ�󶨵���ǰ��¼��ָ�����ֶ�
	 * @param[ in ] column �ֶ��ڼ�¼�е�����,��0��ʼ
	 * @param[ out ] value ָ����ֵ
	 * @exception OutOfRangeException ������Χ��¼������
	 */
	 bool bind( int index, double value )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->bind( index, value );
	 }

	/**
	 * ��ֵ�󶨵���ǰ��¼��ָ�����ֶ�
	 * @param[ in ] column �ֶ��ڼ�¼�е�����,��0��ʼ
	 * @param[ out ] value ָ����ֵ
	 * @exception OutOfRangeException ������Χ��¼������
	 */
	 bool bind( int index, const char* str , size_t n )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->bind( index, str, n );
	 }

	/**
	 * ��ֵ�󶨵���ǰ��¼��ָ�����ֶ�
	 * @param[ in ] column �ֶ��ڼ�¼�е�����,��0��ʼ
	 * @param[ out ] value ָ����ֵ
	 * @exception OutOfRangeException ������Χ��¼������
	 */
	 bool bind( int index, const Timestamp& time )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->bind( index, time );
	 }

	/**
	 * ��ֵ�󶨵���ǰ��¼��ָ�����ֶ�
	 * @param[ in ] columnName ����
	 * @param[ out ] value ָ����ֵ
	 * @exception IllegalArgumentException û���ҵ�����Ϊ columnName ����
	 */
	 bool bind( const tchar* columnName, bool value )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->bind( columnName, value );
	 }

	/**
	 * ��ֵ�󶨵���ǰ��¼��ָ�����ֶ�
	 * @param[ in ] columnName ����
	 * @param[ out ] value ָ����ֵ
	 * @exception IllegalArgumentException û���ҵ�����Ϊ columnName ����
	 */
	 bool bind( const tchar* columnName, int8_t value )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->bind( columnName, value );
	 }

	/**
	 * ��ֵ�󶨵���ǰ��¼��ָ�����ֶ�
	 * @param[ in ] columnName ����
	 * @param[ out ] value ָ����ֵ
	 * @exception IllegalArgumentException û���ҵ�����Ϊ columnName ����
	 */
	 bool bind( const tchar* columnName, int16_t value )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->bind( columnName, value );
	 }

	/**
	 * ��ֵ�󶨵���ǰ��¼��ָ�����ֶ�
	 * @param[ in ] columnName ����
	 * @param[ out ] value ָ����ֵ
	 * @exception IllegalArgumentException û���ҵ�����Ϊ columnName ����
	 */
	 bool bind( const tchar* columnName, int32_t value )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->bind( columnName, value );
	 }

	/**
	 * ��ֵ�󶨵���ǰ��¼��ָ�����ֶ�
	 * @param[ in ] columnName ����
	 * @param[ out ] value ָ����ֵ
	 * @exception IllegalArgumentException û���ҵ�����Ϊ columnName ����
	 */
	 bool bind( const tchar* columnName, int64_t value )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->bind( columnName, value );
	 }

	/**
	 * ��ֵ�󶨵���ǰ��¼��ָ�����ֶ�
	 * @param[ in ] columnName ����
	 * @param[ out ] value ָ����ֵ
	 * @exception IllegalArgumentException û���ҵ�����Ϊ columnName ����
	 */
	 bool bind( const tchar* columnName, double value )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->bind( columnName, value );
	 }

	/**
	 * ��ֵ�󶨵���ǰ��¼��ָ�����ֶ�
	 * @param[ in ] columnName ����
	 * @param[ out ] value ָ����ֵ
	 * @exception IllegalArgumentException û���ҵ�����Ϊ columnName ����
	 */
	 bool bind( const tchar* columnName, const char* str , size_t n )
	 {
		if( null_ptr == _command )
			ThrowException( NullException );
		return _command->bind( columnName, str, n );
	 }

	/**
	 * ��ֵ�󶨵���ǰ��¼��ָ�����ֶ�
	 * @param[ in ] columnName ����
	 * @param[ out ] value ָ����ֵ
	 * @exception IllegalArgumentException û���ҵ�����Ϊ columnName ����
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
