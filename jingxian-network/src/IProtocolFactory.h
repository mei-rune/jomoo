
#ifndef _PROTOCOLFACTORY_H_
#define _PROTOCOLFACTORY_H_

#include "config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
#include "protocol.h"

_jingxian_begin

class IProtocolFactory
{
public:

	virtual ~ProtocolFactory(){}

	virtual IProtocol* createProtocol() = 0;

	static void release( IProtocol* pr );
};

_jingxian_end

#endif // _PROTOCOLFACTORY_H_