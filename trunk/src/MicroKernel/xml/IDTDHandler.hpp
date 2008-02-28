#ifndef DTDHANDLER_HPP
#define DTDHANDLER_HPP

# include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_MicroKernel.h"

_micro_kernel_xml_begin

class IDTDHandler
{
public:

	virtual ~IDTDHandler(){}

	virtual void notationDecl
    (
          const string_view&    name
        , const string_view&    publicId
        , const string_view&    systemId
    ) = 0;


    virtual void unparsedEntityDecl
    (
          const string_view&    name
        , const string_view&    publicId
        , const string_view&    systemId
        , const string_view&    notationName
    ) = 0;

    virtual void resetDocType() = 0;
};

_micro_kernel_xml_end

#endif
