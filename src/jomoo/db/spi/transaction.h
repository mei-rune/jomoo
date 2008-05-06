
#ifndef __TRANSACTION__
#define __TRANSACTION__

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_db.h"
#include "IConnection.h"

_jomoo_db_begin

namespace spi
{

class transaction
{
public:
	virtual ~transaction() {}

	/**
	 * 取得得事务的 IsolationLevel
	 */
	virtual IsolationLevel level() const = 0;

	/**
	 * 提交事务
	 */
	virtual bool commit()   = 0;

	/**
	 * 回滚事务
	 */
	virtual bool rollback() = 0;
};

}

_jomoo_db_end

#endif // __TRANSACTION__
