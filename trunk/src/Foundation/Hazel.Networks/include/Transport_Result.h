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
	 * ���β�����key
	 */
	virtual void* act() = 0;

	/**
	 * ���βٲ������Ƿ�ɹ�
	 * @return ����true��ʾ�����ǳɹ��ģ�����ʧ�ܵ�
	 */
	virtual bool success() const = 0;

	/**
	 * ȡ�ô���ԭ��
	 * @return ����0��ʾû�д��󣬷��򷵻ش����
	 */
	virtual int error() const = 0;

};// END CLASS DEFINITION Hazel_Transport_Result

_networks_end

#endif // __Hazel_CHANNEL_RESULT__
