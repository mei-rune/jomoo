
#ifndef _DbQuery_H_
#define _DbQuery_H_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_db.h"
# include "jomoo/datetime.h"
# include "jomoo/timespan.h"
# include "jomoo/Timestamp.h"

_jomoo_db_begin

class DbQuery {
public:
	virtual ~DbQuery() {}

	/**
	 * ִ��sql���
	 * @param[ in ] sql sql���
	 * @param[ in ] len sql���ĳ���,Ĭ��Ϊ-1��ʾ��֪���ж೤
	 * @param[ in ] reportWarningsAsErrors �Ƿ񽫾��浱�ɴ���
	 */
	virtual bool exec(const tchar* sql, size_t len = -1, bool reportWarningsAsErrors = true ) = 0;

	/**
	 * ִ��sql���
	 * @param[ in ] sql sql���
	 * @param[ in ] reportWarningsAsErrors �Ƿ񽫾��浱�ɴ���
	 */
	virtual bool exec(const tstring& sql, bool reportWarningsAsErrors = true ) = 0;

	/**
	 * �л�����һ����¼
	 */
	virtual bool nextRow() = 0;

	/**
	 * �л�����һ��¼��
	 */
	virtual bool nextSet() = 0;

	/**
	 * ȡ�õ�ǰ������ж�����
	 */
	virtual int columns() = 0;

	/**
	 * ȡ��ָ���е���������,���ö�� DBType
	 * @see DBType
	 */
	virtual int columnType( size_t pos ) = 0;

	/**
	 * ȡ��ָ���е�����
	 */
	virtual const tchar* columnName( size_t pos ) = 0;

	virtual bool read(u_int_t column, bool& value) = 0;
	virtual bool read(const tchar* columnName, bool& value) = 0;

	virtual bool read(u_int_t column, int8_t& value) = 0;
	virtual bool read(const tchar* columnName, int8_t& value) = 0;

	virtual bool read(u_int_t column, int16_t& value) = 0;
	virtual bool read(const tchar* columnName, int16_t& value) = 0;

	virtual bool read(u_int_t column, int32_t& value) = 0;
	virtual bool read(const tchar* columnName, int32_t& value) = 0;

	virtual bool read(u_int_t column, int64_t& value) = 0;
	virtual bool read(const tchar* columnName, int64_t& value) = 0;

	virtual bool read(u_int_t column, Timestamp& value) = 0;
	virtual bool read(const tchar* columnName, Timestamp& value) = 0;

	virtual bool read(u_int_t column, double& value) = 0;
	virtual bool read(const tchar* columnName, double& value) = 0;

	virtual bool read(u_int_t column, char* buf, size_t& len ) = 0;
	virtual bool read(const tchar* columnName, char* buf, size_t& len ) = 0;

	virtual void incRef() = 0;
    virtual void decRef() = 0;
};

_jomoo_db_end

#endif // _DbQuery_H_
