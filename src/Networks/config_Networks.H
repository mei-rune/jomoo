

#ifndef _Config_Networks_H
#define _Config_Networks_H


#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "Base/Logger.H"
# include "Base/Counter_Ptr.hpp"

#define _networks_begin
#define _networks_end
#define _networks

#ifndef NetWorksLoggerPtr
#define NetWorksLoggerPtr Hazel_Log_Impl*
#endif 

#endif // _Config_Networks_H