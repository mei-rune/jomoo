

#ifndef _Config_DB_H
#define _Config_DB_H


#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "jomoo/logging/logger.h"
# include "jomoo/counter_ptr.hpp"

#define _jomoo_db_begin _jomoo_begin namespace DB {
#define _jomoo_db_end _jomoo_end }
#define _jomoo_db _jomoo DB::

#endif // _Config_DB_H