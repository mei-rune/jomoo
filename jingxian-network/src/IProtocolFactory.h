
#ifndef _PROTOCOLFACTORY_H_
#define _PROTOCOLFACTORY_H_

#include "config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files

_jingxian_begin

class IProtocol;

class IProtocolFactory
{
public:

	virtual ~ProtocolFactory(){}

	virtual IProtocol* createProtocol() = 0;

	virtual void release( IProtocol* pr );

	/**
	* 取得地址的描述
	*/
	virtual const tstring& toString() const = 0;
};

inline tostream& operator<<( tostream& target, const IProtocolFactory& protocolFactory )
{
	target << protocolFactory.toString();
	return target;
}

_jingxian_end

#endif // _PROTOCOLFACTORY_H_