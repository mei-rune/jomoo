

#ifndef _config_Util_H
#define _config_Util_H


#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include <vector>
#include <map>
#include "jomoo/string.hpp"
#include "jomoo/counter_ptr.hpp"

_jomoo_begin

typedef std::map< tstring , tstring > PropertyDict;
typedef counter_ptr< StringSeq > StringSeqPtr;
typedef counter_ptr< PropertyDict > PropertyDictPtr;

_jomoo_end

#endif // _config_Util_H