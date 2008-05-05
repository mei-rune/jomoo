
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
	 * ȡ�õ������ IsolationLevel
	 */
	virtual IsolationLevel level() const = 0;

	/**
	 * �ύ����
	 */
	virtual bool commit()   = 0;

	/**
	 * �ع�����
	 */
	virtual bool rollback() = 0;
};

}

_jomoo_db_end

#endif // __TRANSACTION__
