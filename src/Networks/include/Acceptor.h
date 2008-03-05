
#ifndef JOMOO_ACCEPTOR_H
#define JOMOO_ACCEPTOR_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_Networks.h"
#include "JOMOO_Transport.h"

_networks_begin


class JOMOO_Accept_Handler;
class JOMOO_Acceptor;
typedef counter_ptr< JOMOO_Acceptor > JOMOO_Acceptor_Ptr;

class JOMOO_Accept_Result : virtual public JOMOO_Transport_Result
{
public:

	typedef JOMOO_Transport_Ptr transportptr;
	typedef JOMOO_Accept_Handler handler_type;
	typedef JOMOO_Acceptor acceptor_type;
	typedef JOMOO_Transport transport_type;

	/**
	 * virtual destructor
	 */
	virtual ~JOMOO_Accept_Result(){}

	/**
	 * 取得新建立的channel句柄
	 * @return 新建立的channel句柄
	 */
	virtual JOMOO_Transport_Ptr new_channel() = 0;

	/**
	 * 本次异步操作的回调句柄
	 */
	virtual JOMOO_Accept_Handler& handle() = 0;

	/**
	 * 本次异步操作的acceptor句柄
	 */
	virtual JOMOO_Acceptor& acceptor() = 0;

};// END CLASS DEFINITION JOMOO_Accept_Result

/**
 * @Brief JOMOO_Accept_Handler Acceptor 异步回调接口，@see JOMOO_Transport
 */
class JOMOO_Accept_Handler
{
public:
	
	typedef JOMOO_Accept_Result result_type;

	/**
	 * virtual destructor
	 */
	virtual ~JOMOO_Accept_Handler(){}

	/**
	 * channel连接轮询操作回调接口
	 * @see JOMOO_Accept_Result
	 * @see JOMOO_Transport::accept
	 */
	virtual void onAccept(JOMOO_Accept_Result& result) = 0;

	/**
	 * 取得实例的描述
	 */
	virtual const tstring& toString() const = 0;

};// END CLASS DEFINITION JOMOO_Accept_Handler

class JOMOO_Acceptor
{
public:

	typedef JOMOO_Accept_Handler handler_type;

	/**
	 * virtual destructor
	 */
	virtual ~JOMOO_Acceptor(){}

	/**
	 * 接收一个channel（就是轮询是否有新的channel连接到来）
	 * @param[ in ] handle 异步回调接口,当channel连接轮询操作（不管成功，失
	 *				败，撤消）调用成功，都会回调handle的onAccept接口
	 * @param[ in ] act 本次操作的的key
	 * @return 成功调用异步channel连接轮询操作则返回true,否则返回false
	 * @remark 注意如果返回成功，并不代表有新的channel连接到来，也不代表一定
	 *		   会新的channel连接到来，但一定会回调handle的onAccept接口，
	 *		   如果返回失败则一定不会调用handle的onAccept接口。
	 * @see JOMOO_Accept_Handler
	 */
	virtual bool accept( JOMOO_Accept_Handler& handle
							/*,JOMOO_Transport_Ptr new_channel*/ 
							, void* act ) = 0;

	/**
	 * 取消接收一个channel（就是取消轮询是否有新的channel连接到来）
	 * @return 成功取消异步channel连接轮询操作则返回true,否则返回false
	 * @see JOMOO_Accept_Handler
	 */
	virtual bool cancel() = 0;

	/**
	 * 取得实例的描述
	 */
	virtual const tstring& toString() const = 0;
};

_networks_end

#endif
