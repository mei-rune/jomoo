
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
	 * 地址的
	 */
	virtual const tstring& protocol() const = 0;

	/**
	 * 取得地址的内存地址
	 */
	virtual const void* addr() const = 0;

	/**
	 * 取得地址的内存块大小
	 */
	virtual size_t size (void) const = 0;

	/**
	 * 取得地址的描述
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
