
#ifndef _serialize_context_h_
#define _serialize_context_h_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "config_serializing.h"
#include "jomoo/exception.hpp"

_serializing_begin

class serialize_context
{
public:
	virtual ~serialize_context(){};

	/**
	 * ���л�����һ��
	 */
	virtual void push( const tstring& className, const tstring& fieldName) = 0;

	/**
	 * ���л�����һ��
	 */
	virtual void pop( ) = 0;

	/**
	 * ��ǰ��������
	 */
	virtual const tstring& currentClass() const = 0;

	/**
	 * ��ǰ�����ֶ���
	 */
	virtual const tstring& currentField() const = 0;

	/**
	 * ��ǰ���
	 */
	virtual size_t depth() const = 0;

	/**
	 * ȡ��level�����ֶ���
	 */
	virtual const tstring& getClass( int level ) const = 0;

	/**
	 * ȡ��level��������
	 */
	virtual const tstring& getField( int level ) const = 0;


	/**
	 * ȡ�õ�ǰ�����ֵ��м���Ϊkey��ֵ
	 * @remarks ע��ȡ����ʱ���׳�NotFindException�쳣
	 */
	virtual const tstring& operator[](const tstring& key) const = 0;


};

_serializing_end

#endif // _serialize_context_h_