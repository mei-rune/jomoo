
#ifndef _IListeningPort_H_
#define _IListeningPort_H_

#include "config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include "connector.h"
# include "acceptor.h"

_jingxian_begin

public class IListeningPort
{
public:

	virtual ~IListeningPort(){};

	virtual const IEndpoint& bindPoint() const = 0 ;

	virtual IAcceptor& acceptor() = 0;

	virtual IProtocolFactory& protocolFactory() = 0;
	
	virtual const IDictionary& misc() const = 0;

	virtual IDictionary& misc() = 0;
};


_jingxian_end

#endif // _IListeningPort_H_
