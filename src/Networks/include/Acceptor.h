
#ifndef Hazel_ACCEPTOR_H
#define Hazel_ACCEPTOR_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_Networks.h"
#include "Hazel_Transport.h"

_networks_begin


class Hazel_Accept_Handler;
class Hazel_Acceptor;
typedef counter_ptr< Hazel_Acceptor > Hazel_Acceptor_Ptr;

class Hazel_Accept_Result : virtual public Hazel_Transport_Result
{
public:

	typedef Hazel_Transport_Ptr transportptr;
	typedef Hazel_Accept_Handler handler_type;
	typedef Hazel_Acceptor acceptor_type;
	typedef Hazel_Transport transport_type;

	/**
	 * virtual destructor
	 */
	virtual ~Hazel_Accept_Result(){}

	/**
	 * 取得新建立的channel句柄
	 * @return 新建立的channel句柄
	 */
	virtual Hazel_Transport_Ptr new_channel() = 0;

	/**
	 * 本次异步操作的回调句柄
	 */
	virtual Hazel_Accept_Handler& handle() = 0;

	/**
	 * 本次异步操作的acceptor句柄
	 */
	virtual Hazel_Acceptor& acceptor() = 0;

};// END CLASS DEFINITION Hazel_Accept_Result

/**
 * @Brief Hazel_Accept_Handler Acceptor 异步回调接口，@see Hazel_Transport
 */
class Hazel_Accept_Handler
{
public:
	
	typedef Hazel_Accept_Result result_type;

	/**
	 * virtual destructor
	 */
	virtual ~Hazel_Accept_Handler(){}

	/**
	 * channel连接轮询操作回调接口
	 * @see Hazel_Accept_Result
	 * @see Hazel_Transport::accept
	 */
	virtual void onAccept(Hazel_Accept_Result& result) = 0;

	/**
	 * 取得实例的描述
	 */
	virtual const tstring& toString() const = 0;

};// END CLASS DEFINITION Hazel_Accept_Handler

class Hazel_Acceptor
{
public:

	typedef Hazel_Accept_Handler handler_type;

	/**
	 * virtual destructor
	 */
	virtual ~Hazel_Acceptor(){}

	/**
	 * 接收一个channel（就是轮询是否有新的channel连接到来）
	 * @param[ in ] handle 异步回调接口,当channel连接轮询操作（不管成功，失
	 *				败，撤消）调用成功，都会回调handle的onAccept接口
	 * @param[ in ] act 本次操作的的key
	 * @return 成功调用异步channel连接轮询操作则返回true,否则返回false
	 * @remark 注意如果返回成功，并不代表有新的channel连接到来，也不代表一定
	 *		   会新的channel连接到来，但一定会回调handle的onAccept接口，
	 *		   如果返回失败则一定不会调用handle的onAccept接口。
	 * @see Hazel_Accept_Handler
	 */
	virtual bool accept( Hazel_Accept_Handler& handle
							/*,Hazel_Transport_Ptr new_channel*/ 
							, void* act ) = 0;

	/**
	 * 取消接收一个channel（就是取消轮询是否有新的channel连接到来）
	 * @return 成功取消异步channel连接轮询操作则返回true,否则返回false
	 * @see Hazel_Accept_Handler
	 */
	virtual bool cancel() = 0;

	/**
	 * 取得实例的描述
	 */
	virtual const tstring& toString() const = 0;
};

_networks_end

#endif
