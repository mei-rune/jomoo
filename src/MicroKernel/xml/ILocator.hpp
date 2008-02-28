#ifndef LOCATOR_HPP
# define LOCATOR_HPP

# include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_MicroKernel.h"

_micro_kernel_xml_begin

class ILocator
{
public:

	virtual ~ILocator(){}

    virtual const string_view& get_public_id() const = 0;

    virtual const string_view& get_system_id() const = 0;

    virtual size_t get_line_number() const = 0;

    virtual size_t get_column_number() const = 0;
};

_micro_kernel_xml_end

#endif
