#ifndef ATTRIBUTES_HPP
# define ATTRIBUTES_HPP

# include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "../config_MicroKernel.h"
# include <map>
# include "ElementName.hpp"

_micro_kernel_xml_begin

class Attribute
{
public:
	ElementName Name;
	string_view Type;
	string_view Value;
};

typedef  std::map< ElementName ,  Attribute > Attributes;

_micro_kernel_xml_end

#endif
