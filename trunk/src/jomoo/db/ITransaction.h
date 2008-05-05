
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

class transaction : jomoo_shared
{
public:
	virtual ~transaction() {}

	/**
	 * 获得数据库连接对象
	 * @remarks 所得的数据库连接对象指针的生命周期不可超过本对象
	 */
    virtual connection& connection() = 0;

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
