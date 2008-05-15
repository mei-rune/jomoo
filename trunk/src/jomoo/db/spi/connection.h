

#ifndef _Connection_H_
#define _Connection_H_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "jomoo/db/config_db.h"
# include "jomoo/counter_ptr.hpp"
# include "jomoo/exception.hpp"

_jomoo_db_begin

enum DBType
{
	DB_UNKOWN,
	DB_TEXT,
	DB_INTEGER_8,
	DB_INTEGER_16,
	DB_INTEGER_32,
	DB_INTEGER_64,
	DB_DOUBLE,
	DB_TIMESTAMP,
	DB_TIMESPAN,
	DB_BLOB,
	DB_NULL
};

enum DB_ERROR
{
	DB_OK = 0,
	DB_INSUFFICIENT = -1, /* ����buf���� */
	DB_INTERNAL = -2,	  /* ���ݿ��ڲ����� */
	DB_MISMATCH  = -3     /* �������Ͳ�ƥ�� */
	DB_NOTFOUND  = -4     /* ��û���ҵ� */
};

struct columnItem
{
	DBType columnType;
	tstring columnName;
};

/**
 * ָ�����ӵ�����������Ϊ��
 */
enum IsolationLevel
{
 // �޷���д���뼶����ߵ������еĹ���ĸ��ġ� 
 Chaos,
 // �����ڶ�ȡ����ʱ���ֹ��������Ա���������������������֮ǰ���Ը������ݣ��Ӷ����²����ظ��Ķ�ȡ��������ݡ�  
 ReadCommitted,
 // ���Խ����������˼��˵����������������Ҳ�����ܶ�ռ����  
 ReadUncommitted,
 // �ڲ�ѯ��ʹ�õ����������Ϸ��������Է�ֹ�����û�������Щ���ݡ���ֹ�����ظ��Ķ�ȡ�������Կ����л����С�  
 RepeatableRead,
 // �� DataSet �Ϸ��÷�Χ�����Է�ֹ���������֮ǰ�������û������л������ݼ��в����С�  
 Serializable,
 // ͨ����һ��Ӧ�ó��������޸�����ʱ�洢��һ��Ӧ�ó�����Զ�ȡ����ͬ���ݰ汾��������ֹ����ʾ���޷���һ�������п��������������н��еĸ��ģ��������²�ѯҲ����ˡ�
 Snapshot,
 // ����ʹ����ָ�����뼶��ͬ�ĸ��뼶�𣬵����޷�ȷ���ü��� 
 // ��ʹ�� OdbcTransaction ʱ����������� IsolationLevel ���߽� IsolationLevel ����Ϊ Unspecied�����񽫸��ݻ��� ODBC ���������Ĭ�ϸ��뼶����ִ�С�
 Unspecified
};

MakeException( DbException , _T("���ݿ������������!") );

namespace spi
{

class transaction;
class query;
class command;

class connection : jomoo_shared
{
public:
	virtual ~connection() {}

	/**
	 * ����һ�����ݿ�����
	 * @param[ in ] parameters ���Ӳ���,һ����dsn�ַ���
	 * @param[ in ] len ���Ӳ����ַ����ĳ���,Ĭ��Ϊ-1��ʾ��֪�ж೤
	 */
	virtual bool open(const tchar* parameters, size_t len ) = 0;

	/**
	 * �ر����ݿ�����
	 */
	virtual void close() = 0;

	/**
	 * ʹ����һ�����ݿ�
	 * @param[ in ] database ���ݿ�����
	 * @param[ in ] len ���ݿ������ַ����ĳ���,Ĭ��Ϊ-1��ʾ��֪�ж೤
	 */
	virtual bool uses(const tchar* database, size_t len ) = 0;

	/**
	 * ����һ����ѯ����
	 */
	virtual query* createQuery() = 0;

	/**
	 * ����һ��ִ�ж���
	 */
	virtual command* createCommand() = 0;

	/**
	 * ��ʼһ������
	 */
	virtual transaction* beginTransaction( IsolationLevel level )    = 0;

	/**
	 * ȡ�����һ�δ���
	 */
	virtual const tstring& last_error() const = 0;

	/**
	 * ���ݿ�������
	 */
	virtual const tstring& name() const = 0;
};

}

_jomoo_db_end

#endif // _Connection_H_
