
#ifndef _acceptor_h_
#define _acceptor_h_

#include "config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include "buffer.h"
# include "endpoint.h"

_jingxian_begin

class IAcceptor
{
public:

	virtual ~IAcceptor(){}

    virtual  time_t timeout () const = 0;

    virtual const IEndpoint& bindpoint() const = 0;

    virtual void stopListening() = 0;

    virtual void startListening() = 0;

    virtual ProtocolFactory& protocolFactory() = 0;

    virtual IDictionary& misc() = 0;
};

_jingxian_end

#endif //_acceptor_h_ 