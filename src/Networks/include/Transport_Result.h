// Communication


#ifndef __Hazel_CHANNEL_RESULT__
#define __Hazel_CHANNEL_RESULT__

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "../config_Networks.h"
# include "Hazel.Platform/os_networks.h"

_networks_begin

class Hazel_Transport;
class Hazel_Transport_Handler;

class Hazel_Transport_Result
{

public:

	/**
	 * virtual destructor
	 */
	virtual ~Hazel_Transport_Result(){}

	/**
	 * 本次操作的key
	 */
	virtual void* act() = 0;

	/**
	 * 本次操步操作是否成功
	 * @return 返回true表示本次是成功的，否则不失败的
	 */
	virtual bool success() const = 0;

	/**
	 * 取得错误原因
	 * @return 返回0表示没有错误，否则返回错误号
	 */
	virtual int error() const = 0;

};// END CLASS DEFINITION Hazel_Transport_Result

_networks_end

#endif // __Hazel_CHANNEL_RESULT__
