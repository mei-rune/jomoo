


#ifndef DECLHANDLER_HPP
#define DECLHANDLER_HPP

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

namespace XML
{

class SAX2_EXPORT DeclHandler
{
public:

    DeclHandler()
    {
    }

    virtual ~DeclHandler()
    {
    }

    virtual void elementDecl
    (
        const   XMLCh* const    name
        , const XMLCh* const    model
    ) = 0;

    virtual void attributeDecl
    (
        const   XMLCh* const    eName
        , const XMLCh* const    aName
        , const XMLCh* const    type
        , const XMLCh* const    mode
        , const XMLCh* const    value
    ) = 0;

    virtual void internalEntityDecl
    (
        const   XMLCh* const    name
        , const XMLCh* const    value
    ) = 0;

    virtual void externalEntityDecl
    (
        const   XMLCh* const    name
        , const XMLCh* const    publicId
        , const XMLCh* const    systemId
    ) = 0;

private :

    DeclHandler(const DeclHandler&);

    DeclHandler& operator=(const DeclHandler&);
};

} ///namespace UTIL

#endif
