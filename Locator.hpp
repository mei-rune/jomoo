#ifndef LOCATOR_HPP
# define LOCATOR_HPP

# include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

// Include files
#include "config_MicroKernel.h"

class Locator
{
public:

    virtual ~Locator()
    {
    }


    virtual const tchar* getPublicId() const = 0;

    virtual const tchar* getSystemId() const = 0;

    virtual size_t getLineNumber() const = 0;

    virtual size_t getColumnNumber() const = 0;
};


#endif
