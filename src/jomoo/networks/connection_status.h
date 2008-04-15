

#ifndef _connection_status_h_
#define _connection_status_h_

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include "config_Networks.h"

_networks_begin

/**
 * 连接对象的状态
 */
enum connection_status
{
	listening,
	connecting
	connected,
	disconnecting,
	disconnected
};

_networks_end

#endif // _connection_status_h_