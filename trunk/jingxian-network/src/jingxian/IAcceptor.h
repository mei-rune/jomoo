
#ifndef _IAcceptor_H_
#define _IAcceptor_H_

#include "jingxian/config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include "buffer.h"
# include "Dictionary.h"

_jingxian_begin

class IEndpoint;
class IProtocolFactory;

class IAcceptor
{
public:
	virtual ~IAcceptor(){}

    virtual  time_t timeout () const = 0;

    virtual const IEndpoint& bindPoint() const = 0;

    virtual void stopListening() = 0;

    virtual void startListening() = 0;

    virtual IProtocolFactory& protocolFactory() = 0;

    virtual IDictionary& misc() = 0;
	
	virtual const IDictionary& misc() const = 0;

	/**
	* 取得地址的描述
	*/
	virtual const tstring& toString() const = 0;
};

inline tostream& operator<<( tostream& target, const IAcceptor& acceptor )
{
	target << acceptor.toString();
	return target;
}

_jingxian_end

#endif //_IAcceptor_H_ 