

#ifndef ATTRIBUTES_HPP
#define ATTRIBUTES_HPP

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

namespace XML
{

class Attributes
{
public:

    Attributes()
    {
    }

    virtual ~Attributes()
    {
    }

    virtual unsigned int getLength() const = 0;

	virtual const XMLCh* getURI(const unsigned int index) const = 0;

    virtual const XMLCh* getLocalName(const unsigned int index) const = 0;

    virtual const XMLCh* getQName(const unsigned int index) const = 0;

    virtual const XMLCh* getType(const unsigned int index) const = 0;

    virtual const XMLCh* getValue(const unsigned int index) const = 0;

	virtual int getIndex(const XMLCh* const uri, const XMLCh* const localPart ) const = 0 ;

	virtual int getIndex(const XMLCh* const qName ) const = 0 ;

	virtual const XMLCh* getType(const XMLCh* const uri, const XMLCh* const localPart ) const = 0 ;

    virtual const XMLCh* getType(const XMLCh* const qName) const = 0;

	virtual const XMLCh* getValue(const XMLCh* const uri, const XMLCh* const localPart ) const = 0 ;

    virtual const XMLCh* getValue(const XMLCh* const qName) const = 0;

private :

    Attributes(const Attributes&);

    Attributes& operator=(const Attributes&);

};

}

#endif
