
#ifndef _REACTORARBITRARY_H_
#define _REACTORARBITRARY_H_

#include "config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include "IConcurrentPort.h"
# include "IEndpoint.h"
# include "ITransport.h"
# include "IProtocol.h"
# include "IProtocolFactory.h"
# include "IConnector.h"
# include "IAcceptor.h"

_jingxian_begin

public class IReactorCore : public IConcurrentPort
{
public:
	virtual ~IReactorCore() {};

    /**
	 * 创建一个连接器
	 */
    virtual IConnector* connectWith(const tchar* endPoint) = 0;

	
    /**
	 * 创建一个连接器
	 */
    virtual IConnector* connectWith(const tchar* endPoint
			, IDictionary& kw) = 0;

    /**
	 * 创建一个监听服务
	 */
    virtual IAcceptor* listenWith( const tchar* endPoint
			, IProtocolFactory* protocolFactory) = 0;
	
	/**
	 * 开始运行直到调用Interrupt才返回
	 */
	virtual void runForever() = 0;

	/**
	 * 停止运行
	 */
	virtual void interrupt() = 0;

	/**
	 * 将句柄绑定到本端口
	 */
	virtual bool bind(HANDLE systemHandler) = 0;
};

_jingxian_end

#endif // _REACTORARBITRARY_H_