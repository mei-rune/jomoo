
#ifndef _protocolcontext_h_
#define _protocolcontext_h_

#include "jingxian/config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include "buffer.h"
# include "Dictionary.h"

_jingxian_begin

class IAcceptor;
class ITransport;

class ProtocolContext
{
public:
	virtual ~ProtocolContext(){}

	virtual IAcceptor& acceptor() = 0;

	virtual const IAcceptor& acceptor() const = 0;

	virtual ITransport& transport() = 0;

	virtual const IDictionary& misc() const = 0;

	virtual IDictionary& misc() = 0;
};

_jingxian_end

#endif //_protocolcontext_h_