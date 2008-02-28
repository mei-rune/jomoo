

#ifndef LEXICALHANDLER_HPP
#define LEXICALHANDLER_HPP

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

namespace XML
{



class SAX2_EXPORT LexicalHandler
{
public:
    
    LexicalHandler()
    {
    }


    virtual ~LexicalHandler()
    {
    }

    virtual void comment
    (
        const   XMLCh* const    chars
        , const unsigned int    length
    ) = 0;

    virtual void endCDATA () = 0;

  
    virtual void endDTD () = 0;

  
    virtual void endEntity (const XMLCh* const name) = 0;

  
    virtual void startCDATA () = 0;

  
    virtual void startDTD
    (
        const   XMLCh* const    name
        , const   XMLCh* const    publicId
        , const   XMLCh* const    systemId
    ) = 0;

  
    virtual void startEntity (const XMLCh* const name) = 0;

private :

    LexicalHandler(const LexicalHandler&);

	LexicalHandler& operator=(const LexicalHandler&);
};


}

#endif
