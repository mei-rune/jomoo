

#ifndef _Config_Networks_H
#define _Config_Networks_H

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "jomoo/logging/logger.h"
# include "jomoo/Counter_Ptr.hpp"

#define _networks_begin
#define _networks_end
#define _networks

#ifndef NetWorksLoggerPtr
#define NetWorksLoggerPtr ILogger*
#endif 

#endif // _Config_Networks_H