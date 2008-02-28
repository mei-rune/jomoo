

#ifndef _Config_Util_H
#define _Config_Util_H


#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

#define _util_begin  namespace UTIL{
#define _util_end  } 
#define _util UTIL::


#include <vector>
#include <map>
#include "../string.hpp"
#include "../Counter_Ptr.hpp"

_util_begin

typedef std::map< tstring , tstring > PropertyDict;
typedef counter_ptr< StringSeq > StringSeqPtr;
typedef counter_ptr< PropertyDict > PropertyDictPtr;

#ifndef UtilLoggerPtr
#define UtilLoggerPtr Hazel_Log_Impl*
#endif 

_util_end

#endif // _Config_Util_H