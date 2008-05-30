
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
	 * ִ��sql���
	 * @param[ in ] sql_string sql���
	 * @param[ in ] len sql���ĳ���,Ĭ��Ϊ-1��ʾ��֪���ж೤
	 * @param[ in ] reportWarningsAsErrors �Ƿ񽫾��浱�ɴ���
	 */
	bool exec(const tchar* sql_string, size_t len = -1, bool reportWarningsAsErrors = true )
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->exec( sql_string, len, reportWarningsAsErrors);
	}

	/**
	 * ִ��sql���
	 * @param[ in ] sql sql���
	 * @param[ in ] reportWarningsAsErrors �Ƿ񽫾��浱�ɴ���
	 */
	bool exec(const tstring& sql, bool reportWarningsAsErrors = true )
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->exec( sql.c_str(), sql.size(), reportWarningsAsErrors);
	}

	/**
	 * �л�����һ����¼
	 */
	bool nextRow()
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->nextRow( );
	}

	/**
	 * �л�����һ��¼��
	 */
	bool nextSet()
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->nextSet( );
	}

	/**
	 * ȡ�õ�ǰ������ж�����
	 */
	int columns()
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->columns( );
	}

	/**
	 * ȡ��ָ���е���������,���ö�� DBType
	 * @see DBType
	 * @exception OutOfRangeException ������Χ��¼������
	 */
	int columnType( size_t pos )
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->columnType( pos );
	}

	/**
	 * ȡ��ָ���е�����
	 * @exception OutOfRangeException ������Χ��¼������
	 */
	const tchar* columnName( size_t pos )
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->columnName( pos );
	}

	/**
	 * �ӵ�ǰ��¼�ж�ȡָ���е�ֵ
	 * @param[ in ] column ���ڼ�¼�е�����,��0��ʼ
	 * @param[ out ] value ��ȡ��ֵ
	 * @exception OutOfRangeException ������Χ��¼������
	 */
	bool read(u_int_t column, bool& value)
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->read( column, value );
	}

	/**
	 * �ӵ�ǰ��¼�ж�ȡָ��������ֵ
	 * @param[ in ] columnName ����
	 * @param[ out ] value ��ȡ��ֵ
	 * @exception IllegalArgumentException û���ҵ�����Ϊ columnName ����
	 */
	bool read(const tchar* columnName, bool& value)
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->read( columnName, value );
	}

	/**
	 * �ӵ�ǰ��¼�ж�ȡָ���е�ֵ
	 * @param[ in ] column ���ڼ�¼�е�����,��0��ʼ
	 * @param[ out ] value ��ȡ��ֵ
	 * @exception OutOfRangeException ������Χ��¼������
	 */
	bool read(u_int_t column, int8_t& value)
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->read( column, value );
	}
	/**
	 * �ӵ�ǰ��¼�ж�ȡָ��������ֵ
	 * @param[ in ] columnName ����
	 * @param[ out ] value ��ȡ��ֵ
	 * @exception IllegalArgumentException û���ҵ�����Ϊ columnName ����
	 */
	bool read(const tchar* columnName, int8_t& value)
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->read( columnName, value );
	}

	/**
	 * �ӵ�ǰ��¼�ж�ȡָ���е�ֵ
	 * @param[ in ] column ���ڼ�¼�е�����,��0��ʼ
	 * @param[ out ] value ��ȡ��ֵ
	 * @exception OutOfRangeException ������Χ��¼������
	 */
	bool read(u_int_t column, int16_t& value)
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->read( column, value );
	}
	/**
	 * �ӵ�ǰ��¼�ж�ȡָ��������ֵ
	 * @param[ in ] columnName ����
	 * @param[ out ] value ��ȡ��ֵ
	 * @exception IllegalArgumentException û���ҵ�����Ϊ columnName ����
	 */
	bool read(const tchar* columnName, int16_t& value)
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->read( columnName, value );
	}

	/**
	 * �ӵ�ǰ��¼�ж�ȡָ���е�ֵ
	 * @param[ in ] column ���ڼ�¼�е�����,��0��ʼ
	 * @param[ out ] value ��ȡ��ֵ
	 * @exception OutOfRangeException ������Χ��¼������
	 */
	bool read(u_int_t column, int32_t& value)
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->read( column, value );
	}
	/**
	 * �ӵ�ǰ��¼�ж�ȡָ��������ֵ
	 * @param[ in ] columnName ����
	 * @param[ out ] value ��ȡ��ֵ
	 * @exception IllegalArgumentException û���ҵ�����Ϊ columnName ����
	 */
	bool read(const tchar* columnName, int32_t& value)
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->read( columnName, value );
	}

	/**
	 * �ӵ�ǰ��¼�ж�ȡָ���е�ֵ
	 * @param[ in ] column ���ڼ�¼�е�����,��0��ʼ
	 * @param[ out ] value ��ȡ��ֵ
	 * @exception OutOfRangeException ������Χ��¼������
	 */
	bool read(u_int_t column, int64_t& value)
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->read( column, value );
	}
	/**
	 * �ӵ�ǰ��¼�ж�ȡָ��������ֵ
	 * @param[ in ] columnName ����
	 * @param[ out ] value ��ȡ��ֵ
	 * @exception IllegalArgumentException û���ҵ�����Ϊ columnName ����
	 */
	bool read(const tchar* columnName, int64_t& value)
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->read( columnName, value );
	}

	/**
	 * �ӵ�ǰ��¼�ж�ȡָ���е�ֵ
	 * @param[ in ] column ���ڼ�¼�е�����,��0��ʼ
	 * @param[ out ] value ��ȡ��ֵ
	 * @exception OutOfRangeException ������Χ��¼������
	 */
	bool read(u_int_t column, Timestamp& value)
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->read( column, value );
	}

	/**
	 * �ӵ�ǰ��¼�ж�ȡָ��������ֵ
	 * @param[ in ] columnName ����
	 * @param[ out ] value ��ȡ��ֵ
	 * @exception IllegalArgumentException û���ҵ�����Ϊ columnName ����
	 */
	bool read(const tchar* columnName, Timestamp& value)
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->read( columnName, value );
	}

	/**
	 * �ӵ�ǰ��¼�ж�ȡָ���е�ֵ
	 * @param[ in ] column ���ڼ�¼�е�����,��0��ʼ
	 * @param[ out ] value ��ȡ��ֵ
	 * @exception OutOfRangeException ������Χ��¼������
	 */
	bool read(u_int_t column, double& value)
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->read( column, value );
	}

	/**
	 * �ӵ�ǰ��¼�ж�ȡָ��������ֵ
	 * @param[ in ] columnName ����
	 * @param[ out ] value ��ȡ��ֵ
	 * @exception IllegalArgumentException û���ҵ�����Ϊ columnName ����
	 */
	bool read(const tchar* columnName, double& value)
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->read( columnName, value );
	}

	/**
	 * �ӵ�ǰ��¼�ж�ȡָ���е�ֵ
	 * @param[ in ] column ���ڼ�¼�е�����,��0��ʼ
	 * @param[ out ] value ��ȡ��ֵ
	 * @exception OutOfRangeException ������Χ��¼������
	 */
	bool read(u_int_t column, char* buf, size_t& len )
	{
		if( null_ptr == _query )
			ThrowException( NullException );
		return _query->read( column, buf, len );
	}

	/**
	 * �ӵ�ǰ��¼�ж�ȡָ��������ֵ
	 * @param[ in ] columnName ����
	 * @param[ out ] value ��ȡ��ֵ
	 * @exception IllegalArgumentException û���ҵ�����Ϊ columnName ����
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
