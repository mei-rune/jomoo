#ifndef ERRORHANDLER_HPP
#define ERRORHANDLER_HPP

# include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_MicroKernel.h"

_micro_kernel_xml_begin

class IErrorHandler
{
public:

	virtual ~IErrorHandler(){}

    virtual void warning(const SAXParseException& exc) = 0;

    virtual void error(const SAXParseException& exc) = 0;

    virtual void fatalError(const SAXParseException& exc) = 0;

    virtual void resetErrors() = 0;

};

_micro_kernel_xml_end

#endif
