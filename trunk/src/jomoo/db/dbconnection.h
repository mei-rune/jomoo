

#ifndef _DbConnection_H_
#define _DbConnection_H_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_db.h"
# include "spi/connection.h"
# include "jomoo/counter_ptr.hpp"
# include "jomoo/exception.hpp"
# include "dbconnection_impl.h"
# include "DbQuery.h"
# include "DbCommand.h"

_jomoo_db_begin

_jomoo_db_end

#endif // _DbConnection_H_
