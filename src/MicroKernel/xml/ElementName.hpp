#ifndef _ElementName_hpp_
# define _ElementName_hpp_

# include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_MicroKernel.h"

_micro_kernel_xml_begin

class ElementName
{
public:
	string_view uri;
	string_view localname;
	string_view qname;

private:
	DECLARE_NO_COPY_CLASS( ElementName );
};

_micro_kernel_xml_end

#endif //_ElementName_hpp_