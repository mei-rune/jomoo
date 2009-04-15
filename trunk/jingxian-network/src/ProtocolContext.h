
#ifndef _protocolcontext_h_
#define _protocolcontext_h_

#include "config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include "buffer.h"
# include "transport.h"
# include "IDictionary.h"

_jingxian_begin

class ProtocolContext
{
public:
	virtual ~ProtocolContext(){}

	virtual ITransport& transport() = 0;

	virtual const IDictionary& misc() const = 0;

	virtual IDictionary& misc() = 0;
};

_jingxian_end

#endif //_protocolcontext_h_