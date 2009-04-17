

#ifndef _CONNECTION_STATUS_H_
#define _CONNECTION_STATUS_H_

#include "jingxian/config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files

_jingxian_begin

/**
 * 连接对象的状态
 */
enum connection_status
{
	listening,
	connecting,
	connected,
	disconnecting,
	disconnected
};

_jingxian_end

#endif // _CONNECTION_STATUS_H_