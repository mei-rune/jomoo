
#ifndef _IEndpoint_H
#define _IEndpoint_H

#include "config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include "string.hpp"

_jingxian_begin


class IEndpoint
{
public:

	virtual ~IEndpoint() {}

	/**
	 * ��ַ��
	 */
	virtual const tstring& protocol() const = 0;

	/**
	 * ȡ�õ�ַ���ڴ��ַ
	 */
	virtual const void* addr() const = 0;

	/**
	 * ȡ�õ�ַ���ڴ���С
	 */
	virtual size_t size (void) const = 0;

	/**
	 * ȡ�õ�ַ������
	 */
    virtual const tstring& toString() const = 0;
};

inline tostream& operator<<( tostream& target, const IEndpoint& addr )
{
	target << addr.toString();
	return target;
}

_jingxian_end

#endif //_IEndpoint_H
