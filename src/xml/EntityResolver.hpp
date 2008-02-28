


#ifndef ENTITYRESOLVER_HPP
#define ENTITYRESOLVER_HPP

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

class EntityResolver
{
public:

    EntityResolver()
    {
    }


    virtual ~EntityResolver()
    {
    }


    virtual InputSource* resolveEntity
    (
        const   XMLCh* const    publicId
        , const XMLCh* const    systemId
    ) = 0;



private :

    EntityResolver(const EntityResolver&);

    EntityResolver& operator=(const EntityResolver&);

};

#endif
