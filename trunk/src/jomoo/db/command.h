
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
	 * ���벢ִ��sql���
	 * @param[ in ] sql_string sql���
	 * @param[ in ] len sql����ַ����ĳ���,Ĭ��Ϊ-1��ʾ��֪�ж೤
	 * @param[ in ] reportWarningsAsErrors �Ƿ񽫾��浱�ɴ���
	 */
	virtual bool direct_exec( const tchar* sql_string, size_t len = -1 , bool reportWarningsAsErrors = true ) = 0;

	/**
	 * ����sql���
	 * @param[ in ] sql_string sql���
	 * @param[ in ] len sql����ַ����ĳ���,Ĭ��Ϊ-1��ʾ��֪�ж೤
	 * @param[ in ] reportWarningsAsErrors �Ƿ񽫾��浱�ɴ���
	 */
	virtual bool prepare( const tchar* sql_string, size_t len= -1, bool reportWarningsAsErrors = true ) = 0;

	/**
	 * ִ�����
	 */
	virtual bool exec( ) = 0;

	/**
	 * ����ڲ�����,������ʼ
	 */
	virtual bool reset( ) = 0;

	/**
	 * ��Ӱ�������
	 */
	virtual int affected_rows( ) = 0;

	/**
	 * ��ֵ�󶨵���ǰ��¼��ָ�����ֶ�
	 * @param[ in ] column �ֶ��ڼ�¼�е�����,��0��ʼ
	 * @param[ out ] value ָ����ֵ
	 * @exception OutOfRangeException ������Χ��¼������
	 */
	virtual bool bind( int index, bool value ) = 0;

	/**
	 * ��ֵ�󶨵���ǰ��¼��ָ�����ֶ�
	 * @param[ in ] column �ֶ��ڼ�¼�е�����,��0��ʼ
	 * @param[ out ] value ָ����ֵ
	 * @exception OutOfRangeException ������Χ��¼������
	 */
	virtual bool bind( int index, int8_t value ) = 0;

	/**
	 * ��ֵ�󶨵���ǰ��¼��ָ�����ֶ�
	 * @param[ in ] column �ֶ��ڼ�¼�е�����,��0��ʼ
	 * @param[ out ] value ָ����ֵ
	 * @exception OutOfRangeException ������Χ��¼������
	 */
	virtual bool bind( int index, int16_t value ) = 0;

	/**
	 * ��ֵ�󶨵���ǰ��¼��ָ�����ֶ�
	 * @param[ in ] column �ֶ��ڼ�¼�е�����,��0��ʼ
	 * @param[ out ] value ָ����ֵ
	 * @exception OutOfRangeException ������Χ��¼������
	 */
	virtual bool bind( int index, int32_t value ) = 0;

	/**
	 * ��ֵ�󶨵���ǰ��¼��ָ�����ֶ�
	 * @param[ in ] column �ֶ��ڼ�¼�е�����,��0��ʼ
	 * @param[ out ] value ָ����ֵ
	 * @exception OutOfRangeException ������Χ��¼������
	 */
	virtual bool bind( int index, int64_t value ) = 0;

	/**
	 * ��ֵ�󶨵���ǰ��¼��ָ�����ֶ�
	 * @param[ in ] column �ֶ��ڼ�¼�е�����,��0��ʼ
	 * @param[ out ] value ָ����ֵ
	 * @exception OutOfRangeException ������Χ��¼������
	 */
	virtual bool bind( int index, double value ) = 0;

	/**
	 * ��ֵ�󶨵���ǰ��¼��ָ�����ֶ�
	 * @param[ in ] column �ֶ��ڼ�¼�е�����,��0��ʼ
	 * @param[ out ] value ָ����ֵ
	 * @exception OutOfRangeException ������Χ��¼������
	 */
	virtual bool bind( int index, const char* str , size_t n ) = 0;

	/**
	 * ��ֵ�󶨵���ǰ��¼��ָ�����ֶ�
	 * @param[ in ] column �ֶ��ڼ�¼�е�����,��0��ʼ
	 * @param[ out ] value ָ����ֵ
	 * @exception OutOfRangeException ������Χ��¼������
	 */
	virtual bool bind( int index, const Timestamp& time ) = 0;

	/**
	 * ��ֵ�󶨵���ǰ��¼��ָ�����ֶ�
	 * @param[ in ] columnName ����
	 * @param[ out ] value ָ����ֵ
	 * @exception IllegalArgumentException û���ҵ�����Ϊ columnName ����
	 */
	virtual bool bind( const tchar* columnName, bool value ) = 0;

	/**
	 * ��ֵ�󶨵���ǰ��¼��ָ�����ֶ�
	 * @param[ in ] columnName ����
	 * @param[ out ] value ָ����ֵ
	 * @exception IllegalArgumentException û���ҵ�����Ϊ columnName ����
	 */
	virtual bool bind( const tchar* columnName, int8_t value ) = 0;

	/**
	 * ��ֵ�󶨵���ǰ��¼��ָ�����ֶ�
	 * @param[ in ] columnName ����
	 * @param[ out ] value ָ����ֵ
	 * @exception IllegalArgumentException û���ҵ�����Ϊ columnName ����
	 */
	virtual bool bind( const tchar* columnName, int16_t value ) = 0;

	/**
	 * ��ֵ�󶨵���ǰ��¼��ָ�����ֶ�
	 * @param[ in ] columnName ����
	 * @param[ out ] value ָ����ֵ
	 * @exception IllegalArgumentException û���ҵ�����Ϊ columnName ����
	 */
	virtual bool bind( const tchar* columnName, int32_t value ) = 0;

	/**
	 * ��ֵ�󶨵���ǰ��¼��ָ�����ֶ�
	 * @param[ in ] columnName ����
	 * @param[ out ] value ָ����ֵ
	 * @exception IllegalArgumentException û���ҵ�����Ϊ columnName ����
	 */
	virtual bool bind( const tchar* columnName, int64_t value ) = 0;

	/**
	 * ��ֵ�󶨵���ǰ��¼��ָ�����ֶ�
	 * @param[ in ] columnName ����
	 * @param[ out ] value ָ����ֵ
	 * @exception IllegalArgumentException û���ҵ�����Ϊ columnName ����
	 */
	virtual bool bind( const tchar* columnName, double value ) = 0;

	/**
	 * ��ֵ�󶨵���ǰ��¼��ָ�����ֶ�
	 * @param[ in ] columnName ����
	 * @param[ out ] value ָ����ֵ
	 * @exception IllegalArgumentException û���ҵ�����Ϊ columnName ����
	 */
	virtual bool bind( const tchar* columnName, const char* str , size_t n ) = 0;

	/**
	 * ��ֵ�󶨵���ǰ��¼��ָ�����ֶ�
	 * @param[ in ] columnName ����
	 * @param[ out ] value ָ����ֵ
	 * @exception IllegalArgumentException û���ҵ�����Ϊ columnName ����
	 */
	virtual bool bind( const tchar* columnName, const Timestamp& time ) = 0;
};

}

_jomoo_db_end

#endif // _command_h_
