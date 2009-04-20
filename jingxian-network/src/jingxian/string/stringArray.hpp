
#ifndef _ctype_traits_hpp_
#define _ctype_traits_hpp_

#include "jingxian/config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include <ctype.h>
# include "jingxian/string/os_string.hpp"

_jingxian_begin



template<typename charT>
class StringArray
{
public:
	StringArray()
	{}
	~StringArray()
	{}
	
private:
	std::vector<charT*> ptrArray_;
}

_jingxian_end

#endif /* _CASE_FUNCTIONS_HPP_ */