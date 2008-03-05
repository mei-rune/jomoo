// Communication


#ifndef __JOMOO_CHANNEL_RESULT__
#define __JOMOO_CHANNEL_RESULT__

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "../config_Networks.h"
# include "Platform/os_networks.h"

_networks_begin

class JOMOO_Transport;
class JOMOO_Transport_Handler;

class JOMOO_Transport_Result
{

public:

	/**
	 * virtual destructor
	 */
	virtual ~JOMOO_Transport_Result(){}

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

};// END CLASS DEFINITION JOMOO_Transport_Result

_networks_end

#endif // __JOMOO_CHANNEL_RESULT__
