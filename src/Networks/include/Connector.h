
#ifndef JOMOO_CONNECTOR_H
#define JOMOO_CONNECTOR_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */


// Include files
#include "../config_Networks.h"
#include "JOMOO_Transport.h"

_networks_begin

class JOMOO_Connect_Handler;
class JOMOO_Connector;

typedef counter_ptr< JOMOO_Connector > JOMOO_Connector_Ptr;

class JOMOO_Connect_Result : public JOMOO_Transport_Result
{

public:

	typedef JOMOO_Transport transport_type;
	typedef JOMOO_Transport_Ptr transportptr;
	typedef JOMOO_Connect_Handler handler_type;
	typedef JOMOO_Connector connector_type;

	/**
	 * virtual destructor
	 */
	virtual ~JOMOO_Connect_Result(){}

	/**
	 * 取得新建立的channel句柄
	 * @return 新建立的channel句柄
	 */
	virtual JOMOO_Transport_Ptr new_channel() = 0;

	/**
	 * 本次异步操作的回调句柄
	 */
	virtual JOMOO_Connect_Handler& handle() = 0;

	/**
	 * 本次异步操作的connector句柄
	 */
	virtual JOMOO_Connector& connector() = 0;

};// END CLASS DEFINITION JOMOO_Connect_Result

/**
 * @Brief JOMOO_Connect_Handler Connector 异步回调接口，@see JOMOO_Transport
 */
class JOMOO_Connect_Handler
{
public:
	
	typedef JOMOO_Connect_Result result_type;

	/**
	 * virtual destructor
	 */
	virtual ~JOMOO_Connect_Handler(){}

	/**
	 * channel建立连接操作回调接口
	 * @see JOMOO_Connect_Result
	 * @see JOMOO_Transport::connect
	 */
	virtual void onConnect(JOMOO_Connect_Result& result) = 0;

	/**
	 * 取得实例的描述
	 */
	virtual const tstring& toString() const = 0;

};// END CLASS DEFINITION JOMOO_Connect_Handler


class JOMOO_Connector
{
public:
    	
	typedef JOMOO_Connect_Handler handler_type;

	/**
	 * virtual destructor
	 */
	virtual ~JOMOO_Connector(){}

	/**
	 * 建立一个channel
	 * @param[ in ] handle 异步回调接口,当建立channel连接操作（不管成功，失
	 *				败，撤消）调用成功，都会回调handle的onConnect接口
	 * @param[ in ] addr 远程地址
	 * @param[ in ] act 本次操作的的key
	 * @return 成功调用建立channel连接操作则返回true,否则返回false
	 * @remark 注意如果返回成功，并不代表建立channel连接成功，也不代表channel
	 *		   连接一定会建立成功，但一定会回调handle的onConnect接口，
	 *		   如果返回失败则一定不会调用handle的onConnect接口。
	 * @see JOMOO_Connect_Handler
	 */
	virtual bool connect(JOMOO_Connect_Handler& handle
						, void* act ) = 0;
	/**
	 * 取消建立一个channel
	 * @return 成功取消则返回true,否则返回false
	 * @see JOMOO_Connect_Handler
	 */
	virtual bool cancel() = 0;

	/**
	 * 取得实例的描述
	 */
    virtual const std::string& toString() const = 0;
};

_networks_end

#endif
