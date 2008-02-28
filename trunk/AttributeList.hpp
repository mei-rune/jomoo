

#ifndef ATTRIBUTELIST_HPP
#define ATTRIBUTELIST_HPP

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

class AttributeList
{
public:

    AttributeList()
    {
    }

    virtual ~AttributeList()
    {
    }

    virtual unsigned int getLength() const = 0;


    virtual const XMLCh* getName(const unsigned int index) const = 0;

    virtual const XMLCh* getType(const unsigned int index) const = 0;

    virtual const XMLCh* getValue(const unsigned int index) const = 0;

    virtual const XMLCh* getType(const XMLCh* const name) const = 0;

    virtual const XMLCh* getValue(const XMLCh* const name) const = 0;

    virtual const XMLCh* getValue(const char* const name) const = 0;


private :

    AttributeList(const AttributeList&);

    AttributeList& operator=(const AttributeList&);

};


#endif
