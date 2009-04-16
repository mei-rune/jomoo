
#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include "string.hpp"
# include "Exception.hpp"

_jingxian_begin

class IEndpoint;

typedef IProtocol* (*BuildProtocol)( ITransport* transport, void* context);
typedef void (*OnConnectError)( const Exception& exception, void* context);

class IConnector
{
public:

	virtual ~IConnector() {};
    /**
     * 建立一个连接
     * 
     * @param[ in ] buildProtocol 在连接成功时，调用本委托创建一个处理器
     * @param[ in ] throwError  在连接发生错误或初始化处理器发生错误时调
	 * 用本委托，错误异常的类型有两种ConnectError和InitializeError
     * @param[ in ] context 本次连接的上下文
     * @exception ConnectError 在连接发生错误时，调用错误处理委托时将传递</exception>
     * @exception InitializeError 初始化处理器发生错误时，调用错误处理委托时将传递</exception>
	 */
    virtual void connect(BuildProtocol buildProtocol, OnConnectError onConnectError, void* context ) = 0;

	/**
	 * 连接的目标地址
	 */
    virtual const IEndpoint& connectTo() const = 0;

	/**
	* 取得地址的描述
	*/
	virtual const tstring& toString() const = 0;
};

inline tostream& operator<<( tostream& target, const IConnector& connector )
{
	target << connector.toString();
	return target;
}

_jingxian_end

#endif // CONNECTOR_H
