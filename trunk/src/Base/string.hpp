
#ifndef _string_hpp_
#define _string_hpp_

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */


# include "Platform/os_string.h"
# include "string/toString.h"
# include "string/string_view.h"
# include "string/stringOps.h"
# include "string/stringPtr.h"
# include "string/string_token_iterator.h"
# include "string/string_append_iterator.h"
# include "string/string_traits.hpp"
# include "string/ctype_traits.hpp"
# include "string/functionals.hpp"
# include "string/trim_functions.hpp"


typedef std::vector< tstring > StringSeq;

#endif // _string_hpp_